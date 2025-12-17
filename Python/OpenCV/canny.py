from typing import Optional
import cv2 as cv
import numpy as np

img: Optional[np.ndarray] = cv.imread('Resources/Photos/cats.jpg')
if img is None:
    raise FileNotFoundError("Could not open or find the image")
cv.imshow('Cats', img)

blank = np.zeros(img.shape, dtype='uint8')
cv.imshow('Blank', blank)

gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
cv.imshow('Gray', gray)

blur = cv.GaussianBlur(gray, (7,7), 0)
cv.imshow('Blur', blur)

# canny is used to detect edges in an image.
canny = cv.Canny(blur, 125, 175)
cv.imshow('Canny edges', canny)

# ret, thresh = cv.threshold(gray, 125, 255, cv.THRESH_BINARY)
# cv.imshow('Threshold', thresh)
# ret and thresh are returned by the thresholding function. which is a boolean value indicating whether the thresholding was successful, and thresh is the resulting thresholded image. thresholded image means an image where pixels are either black or white, depending on whether their intensity is above or below a certain threshold value.

# contours is a list of points that define the boundary of a shape in the image.
contours, hierarchies = cv.findContours(canny, cv.RETR_LIST, cv.CHAIN_APPROX_NONE)
# here hirerarchies mean the relationship between contours. For example, it can tell us if a contour is inside another contour.
print(f"{len(contours)} contour(s) found!")

cv.drawContours(blank, contours, -1, (0,0,255), 1)
cv.imshow('Contours Drawn', blank)


while True:
    if cv.waitKey(1) & 0xFF == ord('q'):
        break
cv.destroyAllWindows()
