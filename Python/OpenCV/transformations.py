from typing import Optional
import cv2 as cv
import numpy as np

img: Optional[np.ndarray] = cv.imread('Resources/Photos/park.jpg')
if img is None:
    raise FileNotFoundError("Could not open or find the image")
cv.imshow('Cat', img)

# Translation
def translate(img, x, y):
    transMat = np.array([[1, 0, x], [0, 1, y]], dtype=np.float32)
    dimensions = (img.shape[1], img.shape[0])
    return cv.warpAffine(img, transMat, dimensions)

# -x --> Left
# -y --> Up
# x  --> Right
# y  --> Down
translated = translate(img, 100, 100)
cv.imshow('Translated', translated)

#Rotation
def rotate(img, angle, rotPoint=None):
    (height, width) = img.shape[:2]
    if rotPoint is None:
        rotPoint = (width // 2, height // 2)
    rotMat = cv.getRotationMatrix2D(rotPoint, angle, 1.0)
    dimensions = (width, height)
    return cv.warpAffine(img, rotMat, dimensions)

rotated = rotate(img, 45)
cv.imshow('Rotated', rotated)

# Flipping
fliped = cv.flip(img, 1)
cv.imshow('Flipped', fliped)

while True:
    if cv.waitKey(1) & 0xFF == ord('q'):
        break
cv.destroyAllWindows()
