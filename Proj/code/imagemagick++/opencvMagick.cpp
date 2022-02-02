#include <list> 
#include <Magick++.h>
/**< OpenCV */
#include <opencv2/opencv.hpp>
#include <opencv2/videoio.hpp>

using namespace std; 
using namespace Magick;

#define INPUT_FNAME "../examples/animation.gif"
#define OUTPUT_FNAME "../examples/animation_output.gif"

void Mat2Magick(cv::Mat& src, Magick::Image &mgk);

int main(int /*argc*/,char **/*argv*/) 
{
    using namespace cv;

    std::list<Image> images; 
    //Magick::readImages( &images, INPUT_FNAME ); 
    //for_each ( images.begin(), images.end(), transparentImage( "red" )  );

    cv::VideoCapture capture;
    cv::Mat frame;
#define CAM_IDX 0
    
    capture.open(CAM_IDX, cv::CAP_V4L2);
  if ( !capture.isOpened() ){
    cout << "Capture from CAM "
         << " 0 "
         << " didn't work" << endl;
    return -1;
  }
  namedWindow("result", 1);

  #define MAX_ITER 90
  Magick::Image img;

  for(int j = 0; j < MAX_ITER; j++){
        capture >> frame;
        cv::imshow("result", frame);

        Mat2Magick(frame, img);
        images.push_back(img);
  }

   writeImages( images.begin(), images.end(), OUTPUT_FNAME );

   return 0;
}

void Mat2Magick(cv::Mat& src, Magick::Image &mgk){
    if(src.channels()==4) {        
        mgk = Image(src.cols, src.rows, "BGRA", CharPixel, (char *)src.data);
    }    
    if(src.channels()==3){
        cv::cvtColor(src,src, cv::COLOR_BGR2BGRA);
        mgk = Image(src.cols, src.rows, "BGRA", CharPixel, (char *)src.data);
    }    
    if(src.channels()==1) {      
        cv::cvtColor(src,src, cv::COLOR_GRAY2BGR);
        cv::cvtColor(src,src, cv::COLOR_BGR2BGRA);
        mgk = Image(src.cols, src.rows, "BGRA", CharPixel, (char *)src.data);
    }
}

