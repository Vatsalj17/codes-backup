from typing import Optional
import cv2 as cv
import numpy as np

img: Optional[np.ndarray] = cv.imread('Resources/Photos/park.jpg')
if img is None:
    raise FileNotFoundError("Could not open or find the image")
cv.imshow('Park', img)
gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
# We grayscale first because the gradient calculation is more straightforward and less prone to noise.


# Laplacian
# It means calculating the second-order derivative of the image.
# What it does is detects edges in an image by finding regions of high second-order derivative.
# It's used to highlight regions where the intensity changes sharply, which is characteristic of edges.
# It's special because it uses a simple approximation of the Laplacian operator, which is a second-order derivative operator.
lap = cv.Laplacian(gray, cv.CV_64F)
lap = np.uint8(np.absolute(lap))
cv.imshow('Laplacian', lap) # pyright: ignore

# Sobel
# It means calculating the first-order derivative of the image.
# What it does is detects edges in an image by finding regions of high first-order derivative.
# It's used to highlight regions where the intensity changes sharply, which is characteristic of edges.
# It's special because it uses a simple approximation of the Sobel operator, which is a first-order derivative operator.
sobelx = cv.Sobel(gray, cv.CV_64F, 1, 0)
sobely = cv.Sobel(gray, cv.CV_64F, 0, 1)
sobelCombined = cv.bitwise_or(sobelx, sobely)

cv.imshow('Sobel X', sobelx)
cv.imshow('Sobel Y', sobely)
cv.imshow('Sobel Combined', sobelCombined)

# Canny
# It means calculating the gradient of the image.
# What it does is detects edges in an image by finding regions of high gradient.
# It's used to highlight regions where the intensity changes sharply, which is characteristic of edges.
# It's special because it uses a Gaussian filter to reduce noise, then calculates the gradient, then applies non-maximum suppression, and finally uses hysteresis thresholding to detect edges.
# Canny is a multi stage process that consists of the following steps:
    # 1. Noise reduction using a Gaussian filter.
    # 2. Finding the intensity gradients of the image.
    # 3. Non-maximum suppression.
    # 4. Double thresholding.
    # 5. Edge tracking by hysteresis.
canny = cv.Canny(gray, 150, 200)
cv.imshow('Canny', canny)


while True:
    if cv.waitKey(1) & 0xFF == ord('q'):
        break
cv.destroyAllWindows()
