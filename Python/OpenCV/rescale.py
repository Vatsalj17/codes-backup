from typing import Optional
import cv2 as cv
import numpy as np

def rescaleFrame(frame, scale=0.75):
    # Image, video and live
    width = int(frame.shape[1] * scale)
    height = int(frame.shape[0] * scale)
    dimensions = (width, height)
    return cv.resize(frame, dimensions, interpolation=cv.INTER_AREA)

def changeRes(width, height):
    # Live video
    capture.set(3, width)
    capture.set(4, height)

img: Optional[np.ndarray] = cv.imread('Resources/Photos/cat.jpg')
if img is None:
    raise FileNotFoundError("Could not open or find the image")

resized_image = rescaleFrame(img)
cv.imshow('Cat', resized_image)

capture = cv.VideoCapture('Resources/Videos/kitten.mp4') # 0 for webcamcapture

if not capture.isOpened():
    raise IOError("Cannot open video source")

while True:
    isTrue, frame = capture.read()
    if not isTrue:
        break
    frame_resized = rescaleFrame(frame)

    cv.imshow('Video', frame)
    cv.imshow('Video Resized', frame_resized)

    if cv.waitKey(60) & 0xFF == ord('q'):
        break

capture.release()
cv.destroyAllWindows()
