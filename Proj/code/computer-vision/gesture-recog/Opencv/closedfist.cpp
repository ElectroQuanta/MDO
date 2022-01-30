#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include <iostream>
#include <opencv2/objdetect.hpp>
#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;
using namespace cv;

void detectAndDraw(Mat &img, CascadeClassifier &cascade, double scale);

/**
 * @brief Compare rectangles by area (descending)
 * @param a: first rectangle to compare
 * @param b: second rectangle to compare
 * @return comparison result: true if first rectangle area is bigger than second one, otherwise false;
 *
 * detailed
 */
bool compareRects(const cv::Rect &a, const cv::Rect &b){
    return a.area() - b.area();
}


int main(int argc, const char **argv) {
  VideoCapture capture;
  Mat frameCopy, image;
  Mat frame;
  double scale = 1;

  String handCascadePath = "../haarcascade/closed_frontal_palm.xml";
//  String cascadePath = "../haarcascade/palm.xml";
  CascadeClassifier handCascade;

/**< Open camera */
  #define CAM_IDX 0
  capture.open(CAM_IDX);
  if ( !capture.isOpened() )
  {
    cout << "Capture from CAM "
         << " 0 "
         << " didn't work" << endl;
    return -1;
  }
  namedWindow("result", 1);

  /**< Load cascade */
  handCascade.load(handCascadePath);
  if( handCascade.empty() ){
      cout << "ERROR: could not load cascade!" << endl;
      return -1;
  }


  /**< Detect and draw */
    for (;;) {
        capture >> frame;
        if( !frame.empty() )
            detectAndDraw(frame, handCascade, scale);

      if (waitKey(10) >= 0)
          break;
  }

  return 0;
}

void detectAndDraw(Mat &img, CascadeClassifier &cascade, double scale) {
  int i = 0;
  double t = 0;
  vector<Rect> fists;
  const static Scalar colors[] = {CV_RGB(0, 0, 255),   CV_RGB(0, 128, 255),
                                  CV_RGB(0, 255, 255), CV_RGB(0, 255, 0),
                                  CV_RGB(255, 128, 0), CV_RGB(255, 255, 0),
                                  CV_RGB(255, 0, 0),   CV_RGB(255, 0, 255)};
  #define COLORS_SZ 8
  Mat gray;
  Mat smallImg(cvRound(img.rows / scale), cvRound(img.cols / scale), CV_8UC1);

  cvtColor(img, gray, COLOR_BGR2GRAY);
  resize(gray, smallImg, smallImg.size(), 0, 0, INTER_LINEAR);
  equalizeHist(smallImg, smallImg);

//  t = (double)getTickCount();

#define FIST_MIN_SIZE 100 /**< face min size (in pixels) */
#define FIST_MIN_NEIGHBORS 3
#define FIST_SCALE_FACTOR 1.1
#define FIST_FLAGS 0

  cascade.detectMultiScale(smallImg, fists,
                           FIST_SCALE_FACTOR, FIST_MIN_NEIGHBORS,
                           FIST_FLAGS
                           |
                               CASCADE_FIND_BIGGEST_OBJECT
                               //|CV_HAAR_DO_ROUGH_SEARCH
                               | CASCADE_SCALE_IMAGE,
                           Size(FIST_MIN_SIZE, FIST_MIN_SIZE));


  if( ! fists.empty() )
  {

      cout << "Unsorted: " << endl;
      for (auto x : fists)
          cout << x << " " << endl;

      sort(fists.begin(), fists.end(), compareRects);
  
      cout << "Sorted" << endl;
      for (auto x : fists)
          cout << x << " " << endl;
//      rectangle(img, fists.at(0).width, fists

      #define LINE_THICKNESS 2
      #define LINE_TYPE 8
      #define LINE_SHIFT 0
      rectangle(img, fists.at(0), colors[0], LINE_THICKNESS, LINE_TYPE,
                LINE_SHIFT);
      
  }
  
  //for (vector<Rect>::const_iterator r = fists.begin(); r != fists.end();
  //     r++, i++) {
  //    
  //  Point center;
  //  Scalar color = colors[i % COLORS_SZ];
  //  int radius;
  //  center.x = cvRound((r->x + r->width * 0.5) * scale);
  //  center.y = cvRound((r->y + r->height * 0.5) * scale);
  //  radius = cvRound((r->width + r->height) * 0.25 * scale);
  //  rectangle(img, Point(center.x + radius, center.y + radius),
  //            Point(center.x - radius, center.y - radius), color, 1, 8,
  //            0); // circle( img, center, radius, color, 3, 8, 0 );
  //  }
  cv::imshow("result", img);
}
