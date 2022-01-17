// src: https://stackoverflow.com/a/18175863/17836786
#include<opencv2/core/core.hpp>
//#include<opencv2/contrib/contrib.hpp>
#include<opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<iostream>
#include <opencv2/videoio.hpp>
#include<vector>

using namespace std;
using namespace cv;

#define WIDTH 240
#define HEIGHT 240
#define ESC 27
#define KEY_QUIT ESC

int main(){
    VideoCapture cap;
    cap.open(0, CAP_V4L2);

    if(!cap.isOpened()){
        cerr << "Error opening the webcam!" << endl;
        return -1;
    }
    Mat image = imread("../filters/mustache.png", -1);
    cv::resize(image,image, Size(WIDTH, HEIGHT) );  
    Mat frame;
    for(;;){
        cap >> frame; 
        Mat newFrame = frame.clone();
        int cx = (newFrame.cols - HEIGHT) / 2;
        if ( !image.empty() ) {
            // Get a BGR version of the face, since the output is BGR color
            Mat srcBGR = Mat(image.size(), CV_8UC3);
            //cvtColor(image, srcBGR, COLOR_GRAY2BGR);
            // Get the destination ROI (and make sure it is within the image)
            Rect dstRC = Rect(cx, newFrame.rows/2, WIDTH, HEIGHT);
            Mat dstROI = newFrame(dstRC);
            // Copy the pixels from src to dst.
            srcBGR.copyTo(dstROI);
        }
        imshow("frame", newFrame);
        char key = (char) waitKey(30);
        // Exit this loop on escape:
        if(key == KEY_QUIT)
            break;
    }   

    return 0;
}
