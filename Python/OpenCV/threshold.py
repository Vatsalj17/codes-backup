from typing import Optional
import cv2 as cv
import numpy as np

img: Optional[np.ndarray] = cv.imread('Resources/Photos/cats.jpg')
if img is None:
    raise FileNotFoundError("Could not open or find the image")
cv.imshow('Cat', img)


# Thresholding is a technique used to separate an image into regions of different intensity.
# It is often used to create binary images, where pixels are either black or white.

# Convert the image to grayscale
gray_img = cv.cvtColor(img, cv.COLOR_BGR2GRAY)
cv.imshow('Gray Cat', gray_img)

# Simple thresholding
# The first argument is the source image (grayscale)
# The second argument is the threshold value (e.g., 127)
# The third argument is the maximum value to use with the THRESH_BINARY thresholding type (usually 255)
# The fourth argument is the thresholding type
# THRESH_BINARY: If pixel value > threshold, set to max_value, otherwise set to 0
# THRESH_BINARY_INV: If pixel value > threshold, set to 0, otherwise set to max_value
# THRESH_TRUNC: If pixel value > threshold, set to threshold, otherwise set to pixel value
# THRESH_TOZERO: If pixel value > threshold, keep it, otherwise set to 0
# THRESH_TOZERO_INV: If pixel value > threshold, set to 0, otherwise keep it
ret, thresh1 = cv.threshold(gray_img, 127, 255, cv.THRESH_BINARY)
# threshold function returns `two values: the return code and the thresholded image. The return code is 0 if the image is empty, otherwise it is 1. The thresholded image is a binary image where pixels are either black or white.`
cv.imshow('Simple Thresholding', thresh1)

ret, thresh2 = cv.threshold(gray_img, 127, 255, cv.THRESH_BINARY_INV)
cv.imshow('Inverted Binary Thresholding', thresh2)

ret, thresh3 = cv.threshold(gray_img, 127, 255, cv.THRESH_TRUNC)
cv.imshow('Truncated Thresholding', thresh3)

ret, thresh4 = cv.threshold(gray_img, 127, 255, cv.THRESH_TOZERO)
cv.imshow('Zero Thresholding', thresh4)

ret, thresh5 = cv.threshold(gray_img, 127, 255, cv.THRESH_TOZERO_INV)
cv.imshow('Inverted Zero Thresholding', thresh5)

# Adaptive thresholding
# This method computes the threshold for small regions of the image.
# This is useful when the illumination of the image varies.
# The first argument is the source image (grayscale)
# The second argument is the maximum value to use with the THRESH_BINARY thresholding type (usually 255)
# The third argument is the adaptive thresholding method
# ADAPTIVE_THRESH_MEAN_C: Threshold value is the mean of the neighborhood area minus the constant C
# ADAPTIVE_THRESH_GAUSSIAN_C: Threshold value is a weighted sum of the neighborhood values where the weights are a gaussian window, minus the constant C
# The fourth argument is the thresholding type (usually cv.THRESH_BINARY or cv.THRESH_BINARY_INV)
# The fifth argument is the block size (size of the neighborhood area, must be odd)
# The sixth argument is the constant C (a value subtracted from the mean or weighted sum)

adaptive_thresh_mean = cv.adaptiveThreshold(gray_img, 255, cv.ADAPTIVE_THRESH_MEAN_C, cv.THRESH_BINARY, 11, 2)
cv.imshow('Adaptive Mean Thresholding', adaptive_thresh_mean)

adaptive_thresh_gaussian = cv.adaptiveThreshold(gray_img, 255, cv.ADAPTIVE_THRESH_GAUSSIAN_C, cv.THRESH_BINARY, 11, 2)
cv.imshow('Adaptive Gaussian Thresholding', adaptive_thresh_gaussian)


while True:
    if cv.waitKey(1) & 0xFF == ord('q'):
        break
cv.destroyAllWindows()
