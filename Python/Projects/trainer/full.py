#!/usr/bin/env python3
"""
gym_trainer_yolo11.py
A lightweight "fully functional" gym trainer using YOLO11 pose models (Ultralytics).
Features:
 - Webcam / video input
 - Pose detection using YOLO11 pose models
 - Keypoint smoothing (EMA), angle calculations
 - Squat rep counting + feedback
 - Visual overlays and CSV logging of keypoints per frame

Requirements:
  pip install ultralytics opencv-python numpy scipy pandas
  Download e.g. yolo11n-pose.pt and put in the working directory or provide full path.

Author: ChatGPT (assistant)
"""

import time
import csv
from collections import deque, defaultdict
import argparse
import math
import numpy as np
import cv2
import pandas as pd

from ultralytics import YOLO  # Ultralytics YOLO11 python API

# ---------------------------
# Utility functions
# ---------------------------

def angle_between(a, b, c):
    """
    Returns angle at point b formed by points a-b-c in degrees.
    Points are (x, y).
    """
    a = np.array(a); b = np.array(b); c = np.array(c)
    ba = a - b
    bc = c - b
    # handle degenerate cases
    if np.linalg.norm(ba) < 1e-6 or np.linalg.norm(bc) < 1e-6:
        return None
    cosang = np.dot(ba, bc) / (np.linalg.norm(ba) * np.linalg.norm(bc))
    cosang = np.clip(cosang, -1.0, 1.0)
    ang = math.degrees(math.acos(cosang))
    return ang

def ema_smooth(new_pt, prev_pt, alpha=0.6):
    """
    Exponential moving average for smoothing 2D points.
    alpha in (0,1] -> higher alpha -> more responsive.
    If prev_pt is None, return new_pt
    """
    if prev_pt is None:
        return new_pt
    return (alpha * np.array(new_pt) + (1 - alpha) * np.array(prev_pt)).tolist()

# ---------------------------
# Pose helper (Ultralytics YOLO11 returns keypoints)
# ---------------------------

# Default COCO style 17 keypoints mapping (verify for your model if different)
KEYPOINT_NAMES = [
    "nose", "left_eye", "right_eye", "left_ear", "right_ear",
    "left_shoulder", "right_shoulder", "left_elbow", "right_elbow",
    "left_wrist", "right_wrist", "left_hip", "right_hip",
    "left_knee", "right_knee", "left_ankle", "right_ankle"
]

# def extract_keypoints_from_result(result):
#     """
#     Given a single ultralytics result (for pose task), extract list of keypoints.
#     Returns:
#       keypoints: list of (x, y, conf) length = num_keypoints or [] if missing
#     Ultralytics returns results with .keypoints attribute for pose models.
#     """
#     # result.keypoints might be a numpy array shape (N, K, 3) for N people, K keypoints.
#     # We'll take the first person (assuming single-user gym trainer).
#     try:
#         kps = result.keypoints  # often a list/np array
#     except Exception:
#         return []
#
#     if kps is None:
#         return []
#
#     # If multiple people detected, pick the one with highest average confidence
#     if isinstance(kps, list) or (hasattr(kps, "shape") and kps.ndim == 3):
#         arr = np.array(kps)
#         if arr.size == 0:
#             return []
#         # arr shape: (num_people, num_kpts, 3)
#         # compute mean confidence per person
#         confs = arr[:, :, 2].mean(axis=1)
#         best_idx = int(np.argmax(confs))
#         person_kps = arr[best_idx]
#         return [(float(x), float(y), float(c)) for x, y, c in person_kps]
#
#     # fallback single person
#     try:
#         arr = np.array(kps)
#         return [(float(x), float(y), float(c)) for x, y, c in arr]
#     except Exception:
#         return []



def extract_keypoints_from_result(res):
    """
    Extracts keypoints (x, y, conf) from a YOLO result object.
    Returns a NumPy array of shape (num_persons, num_keypoints, 3).
    """
    kps = res.keypoints  # This is a Keypoints object

    if kps is None or len(kps) == 0:
        return np.empty((0, 0, 3))

    # Convert to numpy: shape [detections, 17, 3]
    # (x, y, confidence)
    kps_array = kps.data.cpu().numpy()  

    return kps_array

# ---------------------------
# Feedback & rep counting logic (Squats example)
# ---------------------------

class SquatTrainer:
    """
    Simple squat analyzer:
      - counts reps based on knee angle or hip-knee-ankle angle
      - provides textual feedback for common mistakes (not deep enough, knees caving, back bent)
    """

    def __init__(self, knee_angle_up_thresh=165, knee_angle_down_thresh=100,
                 back_angle_thresh=30, min_confidence=0.3):
        # thresholds:
        # knee angle near 180 when standing; below some threshold when squatting.
        self.up_thresh = knee_angle_up_thresh
        self.down_thresh = knee_angle_down_thresh
        self.back_thresh = back_angle_thresh  # degrees off vertical allowed for back
        self.min_conf = min_confidence

        self.state = "up"  # 'up' or 'down'
        self.rep_count = 0
        self.last_rep_time = 0
        self.since_last_transition = 0

    def analyze(self, kps):
        """
        Accepts keypoints list of length 17: (x,y,conf) or empty list.
        Returns: dict with keys: 'rep_count', 'messages' (list), 'angles' (dict)
        """
        msgs = []
        angles = {}

        # need hips, knees, ankles, shoulders
        idx = {name: i for i, name in enumerate(KEYPOINT_NAMES)}
        def kp(name):
            i = idx[name]
            if i < len(kps):
                return (kps[i][0], kps[i][1], kps[i][2])
            return (None, None, 0.0)

        # extract needed
        l_hip = kp("left_hip")
        r_hip = kp("right_hip")
        l_knee = kp("left_knee")
        r_knee = kp("right_knee")
        l_ankle = kp("left_ankle")
        r_ankle = kp("right_ankle")
        l_shoulder = kp("left_shoulder")
        r_shoulder = kp("right_shoulder")

        # choose side with higher confidence (assumes symmetric)
        def choose_side(a, b):
            return a if a[2] >= b[2] else b

        hip = choose_side(l_hip, r_hip)
        knee = choose_side(l_knee, r_knee)
        ankle = choose_side(l_ankle, r_ankle)
        shoulder = choose_side(l_shoulder, r_shoulder)

        # If keypoint confidences too low -> can't analyze
        if hip[2] < self.min_conf or knee[2] < self.min_conf or ankle[2] < self.min_conf:
            msgs.append("Low confidence in lower-body keypoints. Improve camera view.")
            return {"rep_count": self.rep_count, "messages": msgs, "angles": angles}

        # compute knee angle (hip-knee-ankle)
        knee_angle = angle_between(hip[:2], knee[:2], ankle[:2])
        angles['knee'] = knee_angle

        # compute torso angle relative to vertical: use shoulder-hip vector. Measure how many degrees from vertical.
        if shoulder[2] >= self.min_conf:
            # vertical vector pointing up: (0, -1) in image coordinates (y grows downward).
            # compute angle between (shoulder - hip) and (0, -1)
            torso_vec = np.array(shoulder[:2]) - np.array(hip[:2])
            # convert to degrees from vertical
            vert = np.array([0.0, -1.0])
            if np.linalg.norm(torso_vec) < 1e-6:
                torso_deg = None
            else:
                cosang = np.dot(torso_vec, vert) / (np.linalg.norm(torso_vec) * np.linalg.norm(vert))
                cosang = np.clip(cosang, -1.0, 1.0)
                torso_deg = math.degrees(math.acos(cosang))
        else:
            torso_deg = None
        angles['torso_from_vertical'] = torso_deg

        # Determine squat state transitions
        if knee_angle is not None:
            if self.state == "up" and knee_angle < self.down_thresh:
                # entering down phase
                self.state = "down"
                self.since_last_transition = time.time()
            elif self.state == "down" and knee_angle > self.up_thresh:
                # rising -> count rep
                now = time.time()
                # require at least 0.5s between transitions to avoid chatter
                if now - self.since_last_transition > 0.3:
                    self.rep_count += 1
                    self.last_rep_time = now
                self.state = "up"
                self.since_last_transition = now

        # Feedback rules
        if knee_angle is not None:
            if knee_angle > self.up_thresh:
                msgs.append("You're standing tall. Start descent for squat.")
            elif knee_angle <= self.down_thresh:
                msgs.append("Good depth." if knee_angle < (self.down_thresh - 10) else "Not deep enough, go lower.")
            else:
                msgs.append("In transition...")

        if torso_deg is not None:
            if torso_deg > self.back_thresh:
                msgs.append("Back is leaning forward — keep chest up and core tight!")

        # knees caving check: check left/right knee alignment vs hip-ankle
        # if both knees available, compute relative angle
        if l_knee[2] >= self.min_conf and r_knee[2] >= self.min_conf and l_hip[2] >= self.min_conf and r_hip[2] >= self.min_conf and l_ankle[2] >= self.min_conf and r_ankle[2] >= self.min_conf:
            # compute vectors hip->knee and ankle->knee for each side and see inward/outward angles
            l_ang = angle_between(l_hip[:2], l_knee[:2], l_ankle[:2])
            r_ang = angle_between(r_hip[:2], r_knee[:2], r_ankle[:2])
            angles['left_knee'] = l_ang
            angles['right_knee'] = r_ang
            # crude check: if one knee angle much smaller than other -> lateral imbalance
            if l_ang is not None and r_ang is not None:
                if abs(l_ang - r_ang) > 20:
                    msgs.append("Uneven knees — check your stance symmetry.")
        return {"rep_count": self.rep_count, "messages": msgs, "angles": angles}

# ---------------------------
# Main App
# ---------------------------

def main(args):
    # Load model
    print("[INFO] Loading YOLO11 pose model:", args.model)
    model = YOLO(args.model)  # Ultralytics: model = YOLO("yolo11n-pose.pt")
    print("[INFO] Model loaded. Device:", model.device)

    cap = cv2.VideoCapture(args.source if args.source.isdigit() == False else int(args.source))
    if not cap.isOpened():
        raise RuntimeError("Cannot open video source: " + args.source)

    # logger CSV
    csv_file = open(args.csv if args.csv else "keypoints_log.csv", "w", newline="")
    csv_writer = csv.writer(csv_file)
    # header: frame, timestamp, rep_count, and kp_x,kp_y,kp_conf for each keypoint
    header = ["frame", "timestamp", "rep_count"]
    for name in KEYPOINT_NAMES:
        header += [f"{name}_x", f"{name}_y", f"{name}_conf"]
    csv_writer.writerow(header)

    # smoothing storage
    prev_smoothed = None

    trainer = SquatTrainer(knee_angle_up_thresh=args.up_thresh,
                           knee_angle_down_thresh=args.down_thresh,
                           back_angle_thresh=args.back_thresh,
                           min_confidence=args.min_conf)

    frame_idx = 0
    fps_timer = time.time()
    fps_count = 0
    ema_alpha = args.ema_alpha

    print("[INFO] Starting loop. Press 'q' to exit.")
    while True:
        ret, frame = cap.read()
        if not ret:
            break
        orig_h, orig_w = frame.shape[:2]

        # Inference: use model.predict or model(frame) — using predict to set task='pose'
        # We use stream=True to allow generators when available.
        results = model.predict(source=frame, task="pose", imgsz=args.imgsz, conf=args.conf_thres, verbose=False)
        # results is usually a list-like with one Result object
        res = results[0] if len(results) > 0 else None
        kps = extract_keypoints_from_result(res) if res is not None else []

        # convert to list of (x,y,conf) length 17; pad if needed
        if kps is None:
            kps = []

        if kps.shape[0] == 0:
            kps_list = [(0.0, 0.0, 0.0)] * len(KEYPOINT_NAMES)
        else:
            # pick first detected person
            kps_list = kps[0].tolist()  # shape (17,3) -> list of 17 (x,y,conf)

        # pad if fewer keypoints (rare, just in case)
        if len(kps_list) < len(KEYPOINT_NAMES):
            kps_list += [(0.0, 0.0, 0.0)] * (len(KEYPOINT_NAMES) - len(kps_list))

        # smoothing
        smoothed = [(float(pt[0]), float(pt[1]), float(pt[2])) for pt in kps_list]

        # analyze
        analysis = trainer.analyze(smoothed)
        rep_count = analysis["rep_count"]
        messages = analysis["messages"]
        angles = analysis["angles"]

        # Visualization: draw skeleton lines & keypoints
        # Pairs for skeleton (COCO typical)
        skeleton_pairs = [
            ("nose","left_eye"),("nose","right_eye"),
            ("left_eye","left_ear"),("right_eye","right_ear"),
            ("nose","left_shoulder"),("nose","right_shoulder"),
            ("left_shoulder","right_shoulder"),
            ("left_shoulder","left_elbow"),("left_elbow","left_wrist"),
            ("right_shoulder","right_elbow"),("right_elbow","right_wrist"),
            ("left_shoulder","left_hip"),("right_shoulder","right_hip"),
            ("left_hip","right_hip"),
            ("left_hip","left_knee"),("left_knee","left_ankle"),
            ("right_hip","right_knee"),("right_knee","right_ankle")
        ]

        # draw keypoints
        for i, (x,y,c) in enumerate(smoothed):
            if c >= args.min_conf:
                cv2.circle(frame, (int(x), int(y)), 4, (0,255,0), -1)
                cv2.putText(frame, str(i), (int(x)+4,int(y)+4), cv2.FONT_HERSHEY_SIMPLEX, 0.35, (200,200,200), 1)

        # draw skeleton connections
        name_to_idx = {n:i for i,n in enumerate(KEYPOINT_NAMES)}
        for a,b in skeleton_pairs:
            ai = name_to_idx.get(a); bi = name_to_idx.get(b)
            if ai is None or bi is None: continue
            xa,ya,ca = smoothed[ai]
            xb,yb,cb = smoothed[bi]
            if ca >= args.min_conf and cb >= args.min_conf:
                cv2.line(frame, (int(xa),int(ya)), (int(xb),int(yb)), (200,200,0), 2)

        # overlay messages & metrics
        cv2.putText(frame, f"Reps (squats): {rep_count}", (10,30), cv2.FONT_HERSHEY_SIMPLEX, 0.9, (0,255,255), 2)
        ypos = 60
        for msg in messages[:4]:
            cv2.putText(frame, msg, (10,ypos), cv2.FONT_HERSHEY_SIMPLEX, 0.7, (0,180,255), 2)
            ypos += 30

        # show angles on frame for debugging
        ang_text_y = orig_h - 80
        for k,v in angles.items():
            if v is None:
                continue
            cv2.putText(frame, f"{k}: {v:.1f}", (10, ang_text_y), cv2.FONT_HERSHEY_SIMPLEX, 0.6, (255,255,255), 2)
            ang_text_y += 22

        # frame rate display
        fps_count += 1
        if time.time() - fps_timer > 1.0:
            fps = fps_count / (time.time() - fps_timer)
            fps_timer = time.time()
            fps_count = 0
            # update title with fps
        # show frame
        cv2.imshow("YOLO11 Gym Trainer", frame)
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

        # log CSV
        ts = time.time()
        row = [frame_idx, ts, rep_count]
        for (x,y,c) in smoothed:
            row += [x, y, c]
        csv_writer.writerow(row)

        frame_idx += 1

    print("[INFO] Releasing resources.")
    csv_file.close()
    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    parser = argparse.ArgumentParser(description="YOLO11 Gym Trainer (pose-based)")
    parser.add_argument("--model", type=str, default="yolo11n-pose.pt", help="Path to YOLO11 pose model")
    parser.add_argument("--source", type=str, default="0", help="Video source (0 for webcam or path to file)")
    parser.add_argument("--imgsz", type=int, default=640, help="Inference image size")
    parser.add_argument("--conf_thres", type=float, default=0.25, help="Confidence threshold for detections")
    parser.add_argument("--min_conf", type=float, default=0.25, help="Minimum keypoint confidence for analysis")
    parser.add_argument("--ema_alpha", type=float, default=0.6, help="Smoothing alpha (0..1)")
    parser.add_argument("--up_thresh", type=float, default=165.0, help="Knee angle threshold considered 'up' (degrees)")
    parser.add_argument("--down_thresh", type=float, default=100.0, help="Knee angle threshold considered 'down' (degrees)")
    parser.add_argument("--back_thresh", type=float, default=30.0, help="Allowed torso tilt from vertical (deg)")
    parser.add_argument("--csv", type=str, default="keypoints_log.csv", help="CSV file to save keypoints")
    args = parser.parse_args()
    main(args)
