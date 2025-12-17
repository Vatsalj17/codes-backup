import cv2 as cv

capture = cv.VideoCapture('Resources/Videos/kitten.mp4') # 0 for webcamcapture
# capture = cv.VideoCapture(0) # 0 for webcamcapture

if not capture.isOpened():
    raise IOError("Cannot open video source")

while True:
    isTrue, frame = capture.read()
    if not isTrue:
        break

    # fliped = cv.flip(frame, 1)
    # cv.imshow('Video', fliped)
    cv.imshow('Video', frame)

    if cv.waitKey(20) & 0xFF == ord('q'):
        break

capture.release()
cv.destroyAllWindows()
