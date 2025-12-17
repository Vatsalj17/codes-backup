from typing import Optional
import cv2 as cv
import numpy as np

img: Optional[np.ndarray] = cv.imread('Resources/Photos/cats.jpg')
if img is None:
    raise FileNotFoundError("Could not open or find the image")
cv.imshow('Cats', img)


# Averaging
average = cv.blur(img, (7, 7))
cv.imshow('Average Blur', average)

# GAUSSIAN BLUR is a method of reducing noise by averaging the pixel values in a neighborhood around each pixel. The size of the neighborhood is determined by the kernel size. A larger kernel size will result in more blurring. The sigmaX and sigmaY parameters control the standard deviation of the Gaussian kernel in the X and Y directions, respectively. A larger sigma value will result in more blurring.
# Its different from averageblur method because it uses a weighted average where the weights are determined by a Gaussian function. This means that pixels closer to the center of the kernel have a greater influence on the blurred pixel than pixels further away. This results in a smoother blur that preserves edges better than simple averaging.
gauss = cv.GaussianBlur(img, (7, 7), 0)
cv.imshow('Gaussian Blur', gauss)

# Median Blur
median = cv.medianBlur(img, 7)
cv.imshow('Median Blur', median)

# Bilateral Filter is a special filter that is very effective at reducing noise while preserving edges. It works by applying a weighted average to each pixel, where the weights are determined by both the spatial distance between pixels and the intensity difference between them. This means that pixels that are close in both space and intensity to the current pixel will have a greater influence on the blurred result. This is in contrast to other blurring techniques like Gaussian blur, which only consider spatial distance. The parameters for the bilateral filter are:
# - d: Diameter of each pixel neighborhood that is used during filtering. If it is non-positive, it is computed from sigmaSpace.
# - sigmaColor: Filter sigma in the color space. A larger value means that farther colors within the pixel neighborhood (see sigmaSpace) will be mixed together, resulting in larger areas of semi-equal color.
# - sigmaSpace: Filter sigma in the coordinate space. A larger value means that farther pixels will influence each other as long as their colors are close enough (see sigmaColor).
bilateral = cv.bilateralFilter(img, 10, 35, 35)
cv.imshow('Bilateral Filter', bilateral)


while True:
    if cv.waitKey(1) & 0xFF == ord('q'):
        break
cv.destroyAllWindows()
