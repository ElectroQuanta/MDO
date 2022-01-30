#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include <iostream>
#include <opencv2/objdetect.hpp>
#include <stdio.h>

using namespace std;
using namespace cv;

String cascadeName = "../haarcascade/haarcascade_frontalface_alt2.xml";
String nestedCascadeName = "../haarcascade/haarcascade_eye_tree_eyeglasses.xml";
//String cascadeName2 = "../haarcascade/aGest.xml";
String cascadeName2 = "../haarcascade/closed_frontal_palm.xml";
//String cascadeName2 = "../haarcascade/fist.xml";
//String cascadeName2 = "../haarcascade/palm.xml";

CascadeClassifier cascade, nestedCascade;

int g_switch_value = 0;
// This will be the callback that we give to the
// trackbar.
//

void detectAndDraw(Mat &img, CascadeClassifier &cascade,
                   CascadeClassifier &nestedCascade, double scale);

static void switch_callback(int position, void *) {
  if (position != 0) {
    cascade.load(cascadeName);
    nestedCascade.load(nestedCascadeName);
  } else {
    cascade.load(cascadeName2);
    nestedCascade.load(cascadeName2);
  }
}

int main(int argc, const char **argv) {
    VideoCapture capture;
  Mat frameCopy, image;
  Mat frame;
  double scale = 1;

  #define CAM_IDX 0

  capture.open(CAM_IDX);
  if ( !capture.isOpened() )
    cout << "Capture from CAM "
         << " 0 "
         << " didn't work" << endl;

  namedWindow("result", 1);

//int cv::createTrackbar 	( 	const String &  	trackbarname,
//		const String &  	winname,
//		int *  	value,
//		int  	count,
//		TrackbarCallback  	onChange = 0,
//		void *  	userdata = 0 

//  createTrackbar("Switch", "result", &g_switch_value, 1,
//                 switch_callback); // trackbar

  createTrackbar("Switch", "result", nullptr , 100,
               switch_callback); // trackbar
  cv::setTrackbarPos("Switch", "result", g_switch_value);


  //   cascade.load(cascadeName);
  //   nestedCascade.load(nestedCascadeName);
  switch_callback(g_switch_value, 0);

    for (;;) {
        capture >> frame;
        if( !frame.empty() )
            detectAndDraw(frame, cascade, nestedCascade, scale);

      if (waitKey(10) >= 0)
          break;
  }

  return 0;
}

void detectAndDraw(Mat &img, CascadeClassifier &cascade,
                   CascadeClassifier &nestedCascade, double scale) {
  int i = 0;
  double t = 0;
  vector<Rect> faces;
  const static Scalar colors[] = {CV_RGB(0, 0, 255),   CV_RGB(0, 128, 255),
                                  CV_RGB(0, 255, 255), CV_RGB(0, 255, 0),
                                  CV_RGB(255, 128, 0), CV_RGB(255, 255, 0),
                                  CV_RGB(255, 0, 0),   CV_RGB(255, 0, 255)};
  Mat gray,
      smallImg(cvRound(img.rows / scale), cvRound(img.cols / scale), CV_8UC1);

  cvtColor(img, gray, COLOR_BGR2GRAY);
  resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);
  equalizeHist(smallImg, smallImg);

  t = (double)getTickCount();
  cascade.detectMultiScale(smallImg, faces, 1.1, 2,
                           0 |
                               CASCADE_FIND_BIGGEST_OBJECT
                               //|CV_HAAR_DO_ROUGH_SEARCH
                               | CASCADE_SCALE_IMAGE,
                           Size(30, 30));
  for (vector<Rect>::const_iterator r = faces.begin(); r != faces.end();
       r++, i++) {
    Mat smallImgROI;
    vector<Rect> nestedObjects;
    Point center;
    Scalar color = colors[i % 8];
    int radius;
    center.x = cvRound((r->x + r->width * 0.5) * scale);
    center.y = cvRound((r->y + r->height * 0.5) * scale);
    radius = cvRound((r->width + r->height) * 0.25 * scale);
    rectangle(img, Point(center.x + radius, center.y + radius),
              Point(center.x - radius, center.y - radius), color, 1, 8,
              0); // circle( img, center, radius, color, 3, 8, 0 );
    if (nestedCascade.empty())
      continue;
    smallImgROI = smallImg(*r);
    nestedCascade.detectMultiScale(smallImgROI, nestedObjects, 1.1, 2,
                                   0
                                       //|CV_HAAR_FIND_BIGGEST_OBJECT
                                       //|CV_HAAR_DO_ROUGH_SEARCH
                                       //|CV_HAAR_DO_CANNY_PRUNING
                                       | CASCADE_SCALE_IMAGE,
                                   Size(30, 30));
    for (vector<Rect>::const_iterator nr = nestedObjects.begin();
         nr != nestedObjects.end(); nr++) {
      center.x = cvRound((r->x + nr->x + nr->width * 0.5) * scale);
      center.y = cvRound((r->y + nr->y + nr->height * 0.5) * scale);
      radius = cvRound((nr->width + nr->height) * 0.25 * scale);
      // rectangle(img,Point(center.x+radius,center.y+radius),Point(center.x-radius,center.y-radius),color,1.5,8,0);
      circle(img, center, radius, color, 2, 8, 0);
    }
  }
  cv::imshow("result", img);
}
