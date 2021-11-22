# import the necessary packages
from imutils.video import VideoStream
import argparse
import imutils
import time
import cv2

#Lines 2-6 import our required Python packages. The VideoStream class allows us to access our webcam.
#We have only a single command line argument to parse:

# construct the argument parser and parse the arguments
ap = argparse.ArgumentParser()
ap.add_argument("-c", "--cascade", type=str,
	default="haarcascade_frontalface_default.xml",
	help="path to haar cascade face detector")
args = vars(ap.parse_args())

#The --cascade argument points to our pre-trained Haar cascade face detector residing on disk.
#We then load the face detector and initialize our video stream:

# load the haar cascade face detector from
print("[INFO] loading face detector...")
detector = cv2.CascadeClassifier(args["cascade"])

# initialize the video stream and allow the camera sensor to warm up
print("[INFO] starting video stream...")
vs = VideoStream(src=0).start()
time.sleep(2.0)

#Let’s start reading frames from the video stream:
# loop over the frames from the video stream
while True:
	# grab the frame from the video stream, resize it, and convert it
	# to grayscale
	frame = vs.read()
	frame = imutils.resize(frame, width=500)
	gray = cv2.cvtColor(frame, cv2.COLOR_BGR2GRAY)

	# perform face detection
	rects = detector.detectMultiScale(gray, scaleFactor=1.05,
		minNeighbors=5, minSize=(30, 30),
		flags=cv2.CASCADE_SCALE_IMAGE)

#Inside our while loop, we:
#
#1 Read the next frame from the camera
#2 Resize it to have a width of 500 pixels (smaller frames are faster to process)
#3 Convert the frame to grayscale
#
#Lines 33-35 then perform face detection using our Haar cascade.
#
#The final step is to draw the bounding boxes of the detected faces on our frame:

	# loop over the bounding boxes
	for (x, y, w, h) in rects:
		# draw the face bounding box on the image
		cv2.rectangle(frame, (x, y), (x + w, y + h), (0, 255, 0), 2)

	# show the output frame
	cv2.imshow("Frame", frame)
	key = cv2.waitKey(1) & 0xFF

	# if the `q` key was pressed, break from the loop
	if key == ord("q"):
		break

# do a bit of cleanup
cv2.destroyAllWindows()
vs.stop()

# Line 38 loops over the rects list, containing the:
# 
# 1 Starting x coordinate of the face
# 2 Starting y coordinate of the face
# 3 Width (w) of the bounding box
# 4 Height (h) of the bounding box
# 
# We then display the output frame on our screen.
# 
# Real-time Haar cascade face detection results
# 
# We are now ready to apply face detection in real-time with OpenCV!
# 
# Be sure to access the “Downloads” section of this tutorial to retrieve the source code and pre-trained Haar
# cascade.

# From there, open a shell and execute the following command:
# 
# $ python video_face_detector.py
# [INFO] loading face detector...
# [INFO] starting video stream...
# 
# As you can see, our Haar cascade face detector is running in real-time without an issue!
# 
# If you need to obtain real-time face detection, especially on embedded devices, then consider utilizing Haar
# cascade face detectors.
# 
# Yes, they are not as accurate as more modern face detectors, and yes, they are prone to false-positive
# detections as well, but the benefit is that you’ll gain tremendous speed, and you’ll require less
# computational power.
# 
# Otherwise, if you’re on a laptop/desktop, or you can use a coprocessor such as the Movidius NCS or Google
# Coral USB Accelerator, then use deep learning-based face detection. You’ll obtain far higher accuracy
# and still be able to apply face detection in real-time.
