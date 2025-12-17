from typing import Optional
import cv2 as cv
import numpy as np
import matplotlib.pyplot as plt

img: Optional[np.ndarray] = cv.imread('Resources/Photos/cats.jpg')
if img is None:
    raise FileNotFoundError("Could not open or find the image")

# Histogram is a representation of the distribution of pixel intensities in an image.

gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

blank = np.zeros(img.shape[:2], dtype='uint8')
circle = cv.circle(blank, (img.shape[1] // 2, img.shape[0] // 2), 100, 255, -1)
mask = cv.bitwise_and(gray, gray, mask=circle)

hist = cv.calcHist([gray], [0], mask, [256], [0, 256])
plt.figure()
plt.title("Grayscale Histogram")
plt.xlabel("Bins") # Pixel Intensity
plt.ylabel("# of Pixels")
plt.plot(hist)
plt.xlim([0, 256])
plt.show()

# Color histogram
plt.figure()
plt.title("Color Histogram")
plt.xlabel("Bins")
plt.ylabel("# of Pixels")
colors = ('b', 'g', 'r')
for i, col in enumerate(colors):
    hist = cv.calcHist([img], [i], mask, [256], [0, 256])
    plt.plot(hist, color=col)
    plt.xlim([0, 256])
plt.show()

cv.waitKey(0)
