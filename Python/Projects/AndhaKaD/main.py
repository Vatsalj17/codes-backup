import cv2
import os

# Create a folder to save the images
output_folder = 'room_images'
if not os.path.exists(output_folder):
    os.makedirs(output_folder)

# Open your video file
video_path = 'yolo.mp4' # Make sure this is the correct path
vidcap = cv2.VideoCapture(video_path)

count = 0
frame_rate = 1 # Change this to save more or fewer frames per second
while True:
    # Set the frame position and read it
    vidcap.set(cv2.CAP_PROP_POS_MSEC, (count * 1000 / frame_rate))
    success, image = vidcap.read()
    if not success:
        break # Video has ended
    
    # Save the frame as a JPG file
    cv2.imwrite(os.path.join(output_folder, f"frame_{count}.jpg"), image)
    print(f'Successfully saved frame {count}')
    count += 1

print("Done extracting frames.")
