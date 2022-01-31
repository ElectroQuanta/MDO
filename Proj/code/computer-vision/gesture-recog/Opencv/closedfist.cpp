#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/objdetect/objdetect.hpp"

#include <iostream>
#include <opencv2/objdetect.hpp>
#include <opencv2/videoio.hpp>
#include <stdio.h>
#include <bits/stdc++.h>

using namespace std;
using namespace cv;

#define DEBUG 0

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
  Mat frame;
  double scale = 1;

  String handCascadePath = "../haarcascade/closed_frontal_palm.xml";
//  String cascadePath = "../haarcascade/palm.xml";
  CascadeClassifier handCascade;
  
  #define WINDOW_WIDTH 600
  #define WINDOW_HEIGHT 1024

/**< Open camera */
  #define CAM_IDX 0
  bool ret;
  //capture.set(cv::CAP_PROP_FRAME_WIDTH, ((double)WINDOW_WIDTH));

  capture.open(CAM_IDX, cv::CAP_V4L2);
  if ( !capture.isOpened() )
  {
    cout << "Capture from CAM "
         << CAM_IDX 
         << " didn't work" << endl;
    return -1;
  }


#if defined(DEBUG) && DEBUG == 2
  cout << "Original: "
       << "Width: " << capture.get(cv::CAP_PROP_FRAME_WIDTH) 
       << " Height: " << capture.get(cv::CAP_PROP_FRAME_HEIGHT) 
       << endl;
#endif

  capture.set(cv::CAP_PROP_FRAME_WIDTH, WINDOW_WIDTH);
  capture.set(cv::CAP_PROP_FRAME_HEIGHT, WINDOW_HEIGHT);

#if defined(DEBUG) && DEBUG == 2
  cout << "Actual: "
       << "Width: " << capture.get(cv::CAP_PROP_FRAME_WIDTH) 
       << " Height: " << capture.get(cv::CAP_PROP_FRAME_HEIGHT) 
       << endl;
#endif

  //namedWindow("result");
  namedWindow("result", WINDOW_NORMAL);
  resizeWindow("result", WINDOW_WIDTH, WINDOW_HEIGHT);


   cv::Mat resized;

  /**< Load cascade */
  handCascade.load(handCascadePath);
  if( handCascade.empty() ){
      cout << "ERROR: could not load cascade!" << endl;
      return -1;
  }

#if defined(DEBUG) && DEBUG == 2
  capture >> frame;
  cout << "Rows: " << frame.rows << endl;
  cout << "Cols: " << frame.cols << endl;
#endif

  /**< Detect and draw */
    for (;;) {
        capture >> frame;
        //scale = (frame.cols / ((double)WINDOW_HEIGHT));
        //cout << "scale: " << scale << endl;
        if( !frame.empty() )
        {
            cv::resize(frame, resized,
                       cv::Size(WINDOW_WIDTH, WINDOW_HEIGHT));
            detectAndDraw(frame, handCascade, 1.0/scale);
        }

      if (waitKey(10) >= 0)
          break;
  }

  return 0;
}

void detectAndDraw(Mat &img, CascadeClassifier &cascade, double scale) {
  int i = 0;
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

  static int cnt = 0;
  static int iter = 0;
  static double t = 0;

  cascade.detectMultiScale(smallImg, fists,
                           FIST_SCALE_FACTOR, FIST_MIN_NEIGHBORS,
                           FIST_FLAGS
                           |
                               CASCADE_FIND_BIGGEST_OBJECT
                               //|CV_HAAR_DO_ROUGH_SEARCH
                               | CASCADE_SCALE_IMAGE,
                           Size(FIST_MIN_SIZE, FIST_MIN_SIZE));

  iter++;
  #define MAX_ITER 80 /**< 3 seconds: Desktop */

  static cv::Rect gesture(0,0,0,0);

  cv::Point p;

  if( ! fists.empty() )
  {
      cnt++;

#if defined(DEBUG) && DEBUG == 1
      cout << "Unsorted: " << endl;
      for (auto x : fists)
          cout << x << " " << endl;
#endif

      sort(fists.begin(), fists.end(), compareRects);
  
#if defined(DEBUG) && DEBUG == 1
      cout << "Sorted" << endl;
      for (auto x : fists)
          cout << x << " " << endl;
#endif

      gesture = fists.at(0);
      
      #define LINE_THICKNESS 2
      #define LINE_TYPE 8
      #define LINE_SHIFT 0
      rectangle(img, gesture, colors[0], LINE_THICKNESS, LINE_TYPE,
                LINE_SHIFT);
      
  }
  t = (double)getTickCount() - t;
  if(iter > MAX_ITER ){
      //cout << "detection time =" << t*1000/getTickFrequency()
      //     << "ms" << endl;
      cout << "Nr_iter: " << iter << endl;
      cout << "Cnt: " << cnt << endl;


      if(cnt > iter/3){
          /**< Detected hand gesture */
          cout << "Hand gesture detected!" << endl;
          cout << "detection time ="
               << ((double)getTickCount()) * 1/getTickFrequency()
               << "s" << endl;

          /**< Get middle point */
          p.x = gesture.x + gesture.width/2;
          p.y = gesture.y + gesture.height/2;
          
          
          cout << "Rect: (x, y, w, h) = ("
               << gesture.x << ", "
               << gesture.y << ", "
               << gesture.width << ", "
               << gesture.height << ")"
               << endl;

          cout << "Middle point: (x, y) = ("
               << p.x << ", "
               << p.y << ")"
               << endl;
      }

      t = 0; cnt = 0; iter = 0;
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
