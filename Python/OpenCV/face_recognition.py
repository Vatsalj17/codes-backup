import numpy as np
import cv2 as cv
import os

haar_cascade = cv.CascadeClassifier('haar_face.xml')

features = np.load("features.npy", allow_pickle=True)
lables = np.load("labels.npy", allow_pickle=True)
people = []
for i in os.listdir("/home/Vatsal/Codes/Python/OpenCV/Resources/Faces/train"):
    people.append(i)
print(people)

face_recognizer = cv.face.LBPHFaceRecognizer.create()  # pyright: ignore
face_recognizer.read("face_trained.yml")

img = cv.imread("/home/Vatsal/Codes/Python/OpenCV/Resources/Faces/val/madonna/3.jpg")
if img is None:
    raise FileNotFoundError("Could not open or find the image")
gray = cv.cvtColor(img, cv.COLOR_BGR2GRAY)

faces_rect = haar_cascade.detectMultiScale(gray, 1.1, 4)
for (x, y, w, h) in faces_rect:
    faces_roi = gray[y:y + h, x:x + w]
    label, confidence = face_recognizer.predict(faces_roi)
    # predict function returns the predicted label and the confidence score
    # The confidence score is a measure of how well the detected face matches the training data.
    # A lower confidence score indicates a better match.
    # The label is the predicted identity of the person in the face.
    print(f"Label = {people[label]} with confidence of {confidence}")
    cv.putText(img, str(people[label]), (x, y - 10), cv.FONT_HERSHEY_COMPLEX, 1, (0, 255, 0), 2)
    cv.rectangle(img, (x, y), (x + w, y + h), (0, 255, 0), 2)


cv.imshow("Detected Face", img)

while True:
    if cv.waitKey(1) & 0xFF == ord('q'):
        break
cv.destroyAllWindows()
