from time import sleep
from matplotlib.pyplot import flag
import numpy as np
import face_recognition as fr
import cv2
video_capture = cv2.VideoCapture(0)
ali_image = fr.load_image_file("face.jpg")
face_encoding = fr.face_encodings(ali_image)[0]
known_face_encondings = [face_encoding]
known_face_names = ["ali"]
while True: 
    chek = 0
    ret, frame = video_capture.read()

    rgb_frame = frame[:, :, ::-1]

    face_locations = fr.face_locations(rgb_frame)
    face_encodings = fr.face_encodings(rgb_frame, face_locations)

    for (top, right, bottom, left), face_encoding in zip(face_locations, face_encodings):

        matches = fr.compare_faces(known_face_encondings, face_encoding)

        name = "Unknown"

        face_distances = fr.face_distance(known_face_encondings, face_encoding)

        best_match_index = np.argmin(face_distances)
        if matches[best_match_index]:
            name = known_face_names[best_match_index]
            f = open("face_regression.txt", "w")
            f.write("ali")
            f.close()
            chek = 1
        cv2.rectangle(frame, (left, top), (right, bottom), (225, 0, 0), 2)

        cv2.rectangle(frame, (left, bottom -35), (right, bottom), (225, 0, 0), cv2.FILLED)
        font = cv2.FONT_HERSHEY_SIMPLEX
        cv2.putText(frame, name, (left + 6, bottom - 6), font, 1.0, (225, 225, 225), 1)
       
    cv2.imshow('Webcam_facerecognition', frame)
    
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
    if(chek == 1):
        sleep(3);
        exit(0);

video_capture.release()
cv2.destroyAllWindows()
