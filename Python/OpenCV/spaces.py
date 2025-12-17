from typing import Optional
import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt

img: Optional[np.ndarray] = cv.imread('Resources/Photos/park.jpg')
if img is None:
    raise FileNotFoundError("Could not open or find the image")
cv.imshow('Park', img)


# BGR to grayscale
gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
cv.imshow('Gray', gray)

# BGR to HSV (Hue, Saturation, Value)
hsv = cv.cvtColor(img, cv.COLOR_BGR2HSV)
cv.imshow('HSV', hsv)

# BGR to LAB (Lightness, a, b)
lab = cv.cvtColor(img, cv.COLOR_BGR2LAB)
cv.imshow('LAB', lab)

# BGR to RGB
rgb = cv.cvtColor(img, cv.COLOR_BGR2RGB)
cv.imshow('RGB', rgb)

# HSV to BGR
hsv_bgr = cv.cvtColor(hsv, cv.COLOR_HSV2BGR)
cv.imshow('HSV to BGR', hsv_bgr)


while True:
    if cv.waitKey(1) & 0xFF == ord('q'):
        break
cv.destroyAllWindows()

plt.imshow(rgb)
plt.show()
