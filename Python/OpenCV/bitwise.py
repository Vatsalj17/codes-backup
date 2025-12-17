import cv2 as cv
import numpy as np


blank = np.zeros((400, 400), dtype="uint8")
rectangle= cv.rectangle(blank.copy(), (30, 30), (370, 370), 255, -1)
circle = cv.circle(blank.copy(), (200, 200), 200, 255, -1)

cv.imshow('Rectangle', rectangle)
cv.imshow('Circle', circle)
cv.imshow('Bitwise AND', cv.bitwise_and(rectangle, circle))
cv.imshow('Bitwise OR', cv.bitwise_or(rectangle, circle))
cv.imshow('Bitwise XOR', cv.bitwise_xor(rectangle, circle))
cv.imshow('Bitwise NOT', cv.bitwise_not(rectangle))


while True:
    if cv.waitKey(1) & 0xFF == ord('q'):
        break
cv.destroyAllWindows()
