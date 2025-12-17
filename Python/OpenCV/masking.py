from typing import Optional
import cv2 as cv
import numpy as np

img: Optional[np.ndarray] = cv.imread('Resources/Photos/cats_2.jpg')
if img is None:
    raise FileNotFoundError("Could not open or find the image")
cv.imshow('Cats', img)

blank = np.zeros(img.shape[:2], dtype='uint8')
cv.imshow('Blank', blank)

mask = cv.circle(blank, (img.shape[1]//2, img.shape[0]//2), 100, 255, -1)
cv.imshow('Mask', mask)

masked = cv.bitwise_and(img, img, mask=mask)
cv.imshow('Masked Image', masked)

circle = cv.circle(blank, (img.shape[1]//2, img.shape[0]//2), 100, 255, -1)
rectangle = cv.rectangle(blank, (30, 30), (300, 300), 255, -1)
wierd_shape = cv.bitwise_and(circle, rectangle)
cv.imshow('Wierd Shape', wierd_shape)

wierd_masked = cv.bitwise_and(img, img, mask=wierd_shape)
cv.imshow('Wierd Masked Image', wierd_masked)


while True:
    if cv.waitKey(1) & 0xFF == ord('q'):
        break
cv.destroyAllWindows()
