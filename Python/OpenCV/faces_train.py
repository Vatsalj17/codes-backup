import os
import cv2 as cv
import numpy as np
from typing import List

haar_cascade = cv.CascadeClassifier('haar_face.xml')
dir = "/home/Vatsal/Codes/Python/OpenCV/Resources/Faces/train"
people = []
for i in os.listdir("/home/Vatsal/Codes/Python/OpenCV/Resources/Faces/train"):
    people.append(i)
print(people)

features_list: List[np.ndarray] = []
labels_list: List[int] = []


def create_train():
    for person in people:
        path = os.path.join(dir, person)
        label = people.index(person)
        for img in os.listdir(path):
            img_path = os.path.join(path, img)

            img_array = cv.imread(img_path)
            if img_array is None:
                continue
            gray = cv.cvtColor(img_array, cv.COLOR_BGR2GRAY)

            faces_rect = haar_cascade.detectMultiScale(gray, scaleFactor=1.1, minNeighbors=4)
            for (x, y, w, h) in faces_rect:
                faces_roi = gray[y:y + h, x:x + w]
                features_list.append(faces_roi)
                labels_list.append(label)

# Explaining this function in detail:- 
    # This function iterates through each person in the 'people' list,
    # which represents different individuals whose faces are being trained.
    # For each person, it constructs the full path to their directory.
    # It then assigns a unique numerical label to each person based on their index in the 'people' list.
    # The function then iterates through all the image files within that person's directory.
    # For each image, it reads the image, converts it to grayscale, and then uses a Haar cascade classifier
    # to detect faces within the image.
    # If faces are detected, it extracts the Region of Interest (ROI) for each detected face (the face itself).
    # These face ROIs are then added to the 'features_list', and the corresponding label for that person
    # is added to the 'labels_list'. This process effectively collects all the face images and their associated labels
    # for training the face recognition model.

create_train()
print("Training done ------------------")

features = np.array(features_list, dtype='object')
labels = np.array(labels_list)

print(f"Number of features: {len(features)}")
print(f"Number of labels: {len(labels)}")

face_recognizer = cv.face.LBPHFaceRecognizer.create()  # pyright: ignore
# This line initializes a Local Binary Patterns Histograms (LBPH) face recognizer.
# LBPH is a popular algorithm for face recognition due to its robustness to illumination changes and its computational efficiency.
# The `create()` method is a factory method that returns an instance of the LBPH face recognizer.

# Train the recognizer on the features list and labels
face_recognizer.train(features, labels)

np.save('features.npy', features)
np.save('labels.npy', labels)
face_recognizer.save('face_trained.yml')
