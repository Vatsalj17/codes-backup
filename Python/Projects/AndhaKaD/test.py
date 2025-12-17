import cv2
from ultralytics import YOLO
from typing import Optional, List

class ObstacleDetector:
    def __init__(self):
        self.model: Optional[YOLO] = None
        self.cap: Optional[cv2.VideoCapture] = None
        self.camera_index: int = 0
        
    def load_model(self):
        """Load YOLOv8 model"""
        try:
            print("Loading YOLOv8 model...")
            # Using YOLOv8n (nano) for faster performance
            # Options: yolov8n.pt, yolov8s.pt, yolov8m.pt, yolov8l.pt, yolov8x.pt
            self.model = YOLO('yolov8n.pt')
            print("Model loaded successfully!")
            return True
        except Exception as e:
            print(f"Error loading model: {e}")
            return False
    
    def get_available_cameras(self) -> List[int]:
        """Detect available camera sources"""
        available_cameras: List[int] = []
        print("\nScanning for available cameras...")
        
        # Check up to 10 possible camera indices
        for i in range(10):
            cap = cv2.VideoCapture(i)
            if cap.isOpened():
                ret, _ = cap.read()
                if ret:
                    available_cameras.append(i)
                    print(f"Camera {i}: Available")
                cap.release()
        
        return available_cameras
    
    def select_camera(self, available_cameras: List[int]) -> Optional[int]:
        """Interactive camera selection"""
        if not available_cameras:
            print("No cameras found!")
            return None
        
        print(f"\n{'='*50}")
        print("AVAILABLE CAMERAS")
        print(f"{'='*50}")
        for idx in available_cameras:
            print(f"  [{idx}] Camera {idx}")
        print(f"{'='*50}")
        
        while True:
            try:
                choice = input(f"\nSelect camera index (0-{max(available_cameras)}): ")
                camera_idx = int(choice)
                if camera_idx in available_cameras:
                    return camera_idx
                else:
                    print(f"Invalid choice. Please select from: {available_cameras}")
            except ValueError:
                print("Please enter a valid number.")
            except KeyboardInterrupt:
                return None
    
    def initialize_camera(self, camera_index):
        """Initialize selected camera"""
        self.cap = cv2.VideoCapture(camera_index, cv2.CAP_V4L2)
        if not self.cap.isOpened():
            print(f"Failed to open camera {camera_index}")
            return False
        
        # Set camera properties for better performance
        self.cap.set(cv2.CAP_PROP_FRAME_WIDTH, 1280)
        self.cap.set(cv2.CAP_PROP_FRAME_HEIGHT, 720)
        self.cap.set(cv2.CAP_PROP_FPS, 30)
        
        print(f"Camera {camera_index} initialized successfully!")
        return True
    
    def draw_detections(self, frame, results):
        """Draw bounding boxes and labels on frame"""
        if self.model is None:
            return frame
        
        for result in results:
            boxes = result.boxes
            for box in boxes:
                # Get box coordinates
                x1, y1, x2, y2 = box.xyxy[0].cpu().numpy()
                x1, y1, x2, y2 = int(x1), int(y1), int(x2), int(y2)
                
                # Get confidence and class
                conf = float(box.conf[0])
                cls = int(box.cls[0])
                label = self.model.names[cls]
                
                # Choose color based on object type
                if label in ['person', 'car', 'truck', 'bus', 'motorcycle', 'bicycle']:
                    color = (0, 0, 255)  # Red for important obstacles
                else:
                    color = (0, 255, 0)  # Green for other objects
                
                # Draw bounding box
                cv2.rectangle(frame, (x1, y1), (x2, y2), color, 2)
                
                # Prepare label text
                text = f'{label} {conf:.2f}'
                text_size = cv2.getTextSize(text, cv2.FONT_HERSHEY_SIMPLEX, 0.6, 2)[0]
                
                # Draw label background
                cv2.rectangle(frame, (x1, y1 - text_size[1] - 10), 
                            (x1 + text_size[0], y1), color, -1)
                
                # Draw label text
                cv2.putText(frame, text, (x1, y1 - 5), 
                          cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 255), 2)
        
        return frame
    
    def add_info_panel(self, frame, results, fps):
        """Add information panel to frame"""
        if self.model is None:
            return frame
        
        
        # Create semi-transparent overlay
        overlay = frame.copy()
        cv2.rectangle(overlay, (10, 10), (400, 150), (0, 0, 0), -1)
        frame = cv2.addWeighted(frame, 0.7, overlay, 0.3, 0)
        
        # Count detections by category
        detections = {}
        for result in results:
            for box in result.boxes:
                cls = int(box.cls[0])
                label = self.model.names[cls]
                detections[label] = detections.get(label, 0) + 1
        
        # Display information
        y_offset = 35
        cv2.putText(frame, f"FPS: {fps:.1f}", (20, y_offset), 
                   cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0, 255, 0), 2)
        
        y_offset += 30
        cv2.putText(frame, f"Objects Detected: {len(detections)}", (20, y_offset), 
                   cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255, 255, 255), 2)
        
        y_offset += 25
        for label, count in list(detections.items())[:3]:  # Show top 3
            cv2.putText(frame, f"  {label}: {count}", (20, y_offset), 
                       cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 1)
            y_offset += 20
        
        return frame
    
    def run_detection(self) -> None:
        """Main detection loop"""
        if self.cap is None:
            print("Camera not initialized!")
            return
        
        if self.model is None:
            print("Model not loaded!")
            return
        
        print("\n" + "="*50)
        print("OBSTACLE DETECTION SYSTEM ACTIVE")
        print("="*50)
        print("\nControls:")
        print("  'q' or ESC - Quit")
        print("  's' - Save screenshot")
        print("  'c' - Toggle confidence threshold")
        print("\n")
        
        frame_count = 0
        fps = 0
        conf_threshold = 0.5
        
        while True:
            ret, frame = self.cap.read()
            if not ret:
                print("Failed to read frame!")
                break
            
            # Calculate FPS
            frame_count += 1
            if frame_count % 30 == 0:
                fps = 30 / (cv2.getTickCount() / cv2.getTickFrequency() - 
                           (cv2.getTickCount() / cv2.getTickFrequency() if frame_count == 30 else fps))

            # frame = cv2.flip(frame, 1)
            
            # Run YOLO detection
            results = self.model(frame, conf=conf_threshold, verbose=False)
            
            # Draw detections
            frame = self.draw_detections(frame, results)
            
            # Add info panel
            frame = self.add_info_panel(frame, results, fps)
            
            # Display frame
            cv2.imshow('Obstacle Detection - YOLOv8', frame)
            
            # Handle key presses
            key = cv2.waitKey(1) & 0xFF
            if key == ord('q') or key == 27:  # 'q' or ESC
                break
            elif key == ord('s'):
                filename = f'detection_screenshot_{frame_count}.jpg'
                cv2.imwrite(filename, frame)
                print(f"Screenshot saved: {filename}")
            elif key == ord('c'):
                conf_threshold = 0.3 if conf_threshold == 0.5 else 0.5
                print(f"Confidence threshold: {conf_threshold}")
    
    def cleanup(self):
        """Release resources"""
        if self.cap:
            self.cap.release()
        cv2.destroyAllWindows()
        print("\nResources released. Goodbye!")

def main():
    detector = ObstacleDetector()
    
    # Load YOLO model
    if not detector.load_model():
        print("Failed to load model. Please install: pip install ultralytics")
        return
    
    # Get available cameras
    cameras = detector.get_available_cameras()
    if not cameras:
        print("\nNo cameras detected. Please check your camera connection.")
        return
    
    # Select camera
    camera_idx = detector.select_camera(cameras)
    if camera_idx is None:
        print("\nCamera selection cancelled.")
        return
    
    # Initialize camera
    if not detector.initialize_camera(camera_idx):
        return
    
    try:
        # Run detection
        detector.run_detection()
    except KeyboardInterrupt:
        print("\n\nInterrupted by user.")
    finally:
        detector.cleanup()

if __name__ == "__main__":
    main()
