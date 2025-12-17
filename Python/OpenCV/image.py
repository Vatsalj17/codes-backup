from typing import Optional
import cv2 as cv
import numpy as np

img: Optional[np.ndarray] = cv.imread('Resources/Photos/cat.jpg')
if img is None:
    raise FileNotFoundError("Could not open or find the image")

cv.imshow('Cat', img)

while True:
    if cv.waitKey(1) & 0xFF == ord('q'):
        break
cv.destroyAllWindows()
