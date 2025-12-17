# from typing import Optional
import cv2 as cv
import numpy as np

blank = np.zeros((500, 500, 3), dtype='uint8')
cv.imshow('Blank', blank)


# Paint the image a color
# blank[200:300, 300:400] = 0, 255, 0
# cv.imshow('Green', blank)

# Draw a rectangle
# cv.rectangle(blank, (0, 0), (250, 250), (0, 255, 0), thickness=2)
# cv.rectangle(blank, (0, 0), (blank.shape[0] // 2, blank.shape[1] // 2), (0, 255, 0), thickness=-1)
# cv.imshow('Rectangle', blank)

# Draw a circle
# cv.circle(blank, (blank.shape[0] // 2, blank.shape[1] // 2), 100, (0, 0, 255), thickness=3)
# cv.imshow('Circle', blank)

# Draw a line
cv.line(blank, (0, 0), (blank.shape[0] // 2, blank.shape[1] // 2), (255, 255, 255), thickness=5)
cv.imshow('Line', blank)

# Write Text
cv.putText(blank, 'Hello', (255, 255), cv.FONT_HERSHEY_TRIPLEX, 1.0, (0, 255, 0), 2)
cv.imshow('Text', blank)


while True:
    if cv.waitKey(1) & 0xFF == ord('q'):
        break
cv.destroyAllWindows()
