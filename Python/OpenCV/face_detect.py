from typing import Optional
import cv2 as cv
import numpy as np

img: Optional[np.ndarray] = cv.imread('Resources/Photos/group_1.jpg')
if img is None:
    raise FileNotFoundError("Could not open or find the image")
cv.imshow('Image', img)
gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

# CascadeClassifier is a class that can be used to detect objects in an image
haar_cascade = cv.CascadeClassifier("haar_face.xml")
faces_rect = haar_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=1)
# The detectMultiScale function returns a list of rectangles, where each rectangle is represented by its top-left corner (x, y) and its width (w) and height (h).
# scaleFactor: Parameter specifying how much the image size is reduced at each image scale.
# minNeighbors: Parameter specifying how many neighbors each candidate rectangle should have to retain it.

print(f"Number of faces found = {len(faces_rect)}")

for (x, y, w, h) in faces_rect:
    cv.rectangle(img, (x, y), (x+w, y+h), (0, 255, 0), thickness=2)

cv.imshow('Detected Faces', img)


while True:
    if cv.waitKey(1) & 0xFF == ord('q'):
        break
cv.destroyAllWindows()
