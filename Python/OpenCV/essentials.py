from typing import Optional
import cv2 as cv
import numpy as np

img: Optional[np.ndarray] = cv.imread('Resources/Photos/park.jpg')
if img is None:
    raise FileNotFoundError("Could not open or find the image")
cv.imshow('Cat', img)

# Convert the image to grayscale
gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
cv.imshow('Gray', gray)

# Blur the image
blur = cv.GaussianBlur(img, (7,7), 0)
cv.imshow('Blur', blur)

# Edge cascade
canny = cv.Canny(blur, 125, 175)
cv.imshow('Canny', canny)

if canny is None:
    raise TypeError("canny is None, which is not expected.")

# Dilate the image
kernel = np.ones((3, 3), np.uint8) 
dilated = cv.dilate(canny, kernel, iterations=1)
cv.imshow('Dilated', dilated)

# Eroded the image
eroded = cv.erode(dilated, kernel, iterations=1)
cv.imshow('Eroded', eroded)

# Resize
resized = cv.resize(img, (500, 500), interpolation=cv.INTER_AREA) # INTER_AREA when scaling to lesser pixels than original
cv.imshow('Resized', resized)

# Crop the image
cropped = img[50:200, 200:400]
cv.imshow('Cropped', cropped)


while True:
    if cv.waitKey(1) & 0xFF == ord('q'):
        break
cv.destroyAllWindows()
