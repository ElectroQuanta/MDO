// src: https://stackoverflow.com/a/18175863/17836786
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect.hpp>
#include <opencv4/opencv2/calib3d.hpp>
#include <opencv4/opencv2/imgproc.hpp>
#include <vector>
#include <iostream>

using namespace std;
using namespace cv;

#define WIDTH 240
#define HEIGHT 240
#define ESC 27
#define KEY_QUIT ESC

#define FACE_CASCADE_FNAME "../models/haarcascade_frontalface_alt.xml"
#define FILTER_FNAME "../filters/mustache.png"

cv::CascadeClassifier _face_cascade; /**< Haar cascade to detect faces */

void detectFaces(cv::Mat *frame, std::vector<Rect> *faces){
    using namespace cv;
    Mat frame_gray;
    cvtColor( *frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    //-- Detect faces
//void cv::CascadeClassifier::detectMultiScale 	( 	InputArray  	image,
//		std::vector< Rect > &  	objects,
//		double  	scaleFactor = 1.1,
//		int  	minNeighbors = 3,
//		int  	flags = 0,
//		Size  	minSize = Size(),
//		Size  	maxSize = Size() 
//	) 	
//    std::vector<Rect> faces;
    _face_cascade.detectMultiScale( frame_gray, *faces, 1.1, 3, 0,
                                    Size(150,150) );
}


void transparentOverlay(cv::Mat *frame, cv::Mat overlay, cv::Point pos = {0,0}, int scale = 1.0){
    using namespace cv;
    cv::Mat ov = overlay;

    /**< resize foreground (overlay) according to scale */
    //cv::resize(*overlay, ov, cv::Size(), scale, scale, INTER_LINEAR);

    /**< Get size of foreground and background images */
    int h = ov.rows;
    int w = ov.cols;
    int rows = frame->rows;
    int cols = frame->cols;

    /**< Position of foreground/overlay image */
    int x = pos.x;
    int y = pos.y;

    /**< Loop over all pixels and apply the blending equation */
    for(int i = 0; i < h; i++){
        for(int j = 0; j < w; j++){
            if( (x + i >= rows) || (y + j >= cols) )
                continue;
            //Vec3b pix = ov.at<Vec3b>(y,x);
            float alpha = ov.at<Vec3b>(y,x)[3] / 255.0f;
            frame->at<cv::Vec3b>(j, i) =
                (alpha) * ov.at<cv::Vec3b>(j, i) +
                (1.0f - alpha)* frame->at<cv::Vec3b>(j, i);
        }
    }
}

void drawFacesContour(cv::Mat *frame, std::vector<Rect> *faces){
    
    for ( size_t i = 0; i < faces->size(); i++ )
    {
        rectangle( *frame, faces->at(i), (255, 0, 255), 2);
        //Point center( faces->at(i).x + faces->at(i).width/2,
        //              faces->at(i).y + faces->at(i).height/2 );
        //ellipse( *frame, center,
        //         Size( faces->at(i).width/2, faces->at(i).height/2 ),
        //         0, 0, 360, Scalar( 255, 0, 255 ), 4 );
    }
}

void applyFilter(cv::Mat *frame, cv::Mat *filter, std::vector<Rect> *faces){

    Mat overlay = filter->clone();
    //Mat roi = frame->clone();
    /**< ROI: faces */
    for ( size_t i = 0; i < faces->size(); i++ ){

        int x = faces->at(i).x;
        int y = faces->at(i).y;
        int h = faces->at(i).height;
        int w = faces->at(i).width;
        int ymin = (int)(y + 0.3 * h);
        int ymax = (int)(y + 0.5 * h);

        /**< Scale filter to match ROI */
        cv::resize(*filter, overlay, cv::Size(w, ymax - ymin),
                   0, 0, cv::INTER_CUBIC);


        imshow("Overlay", overlay);
        //imshow("Filter", *filter);

        transparentOverlay( frame, overlay, cv::Point(x - w/2, y + w/2) );
    }
  
}


void transparentOv(cv::Mat *src, cv::Mat *dst, cv::Mat *overlay){
  for (int y = 0; y < src->rows; y++) {
    const cv::Vec3b *src_pixel = src->ptr<cv::Vec3b>(y);
    const cv::Vec4b *ovl_pixel = overlay->ptr<cv::Vec4b>(y);
    cv::Vec3b *dst_pixel = dst->ptr<cv::Vec3b>(y);
    for (int x = 0; x < src->cols; x++, ++src_pixel, ++ovl_pixel, ++dst_pixel) {
      double alpha = (*ovl_pixel).val[3] / 255.0;
      for (int c = 0; c < 3; c++) {
        (*dst_pixel).val[c] = (uchar)((*ovl_pixel).val[c] * alpha +
                                      (*src_pixel).val[c] * (1.0 - alpha));
      }
    }
  }
}

struct img_filter{
    std::string name;
    float ymin_coef;
    float ymax_coef;
    float ypos_coef;
};
typedef struct img_filter img_filter_t;


int main(){

     /**< Initialize CV cascades */
    if( !_face_cascade.load( FACE_CASCADE_FNAME ) )
    {
        std::cerr << "Status:  ERROR:  Could not load face cascade" << endl;
        return -1;
    }

    /**< Open camera */
    VideoCapture cap;
    cap.open(0, CAP_V4L2);
    if(!cap.isOpened()){
        cerr << "Error opening the webcam!" << endl;
        return -1;
    }


    img_filter_t filt = {
        FILTER_FNAME, 0.3, 0.5, 0.6
    };

    /**< Get filter */
    Mat filter = imread(filt.name, -1); // 4-channel BGRA
    //Mat filter = imread(FILTER_FNAME); // 3-channel BGR
    if( filter.empty() ){
        cerr << "Error opening the filter!" << endl;
        return -1;
    }
    
    //cv::resize(image,image, Size(WIDTH, HEIGHT) );

    Mat frame, frame_gray, roi;
    Mat overlay = filter.clone();
    std::vector<Rect> faces;
    for(;;){
        cap >> frame;
        /**< Detect faces and draw them */
        cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
        equalizeHist( frame_gray, frame_gray );
        _face_cascade.detectMultiScale( frame_gray, faces, 1.1, 3, 0,
                                    Size(100,100) );
        
        for ( size_t i = 0; i < faces.size(); i++ )
        {
            //rectangle( frame, faces.at(i), (255, 0, 255), 2);

            int x = faces.at(i).x;
            int y = faces.at(i).y;
            int h = faces.at(i).height;
            int w = faces.at(i).width;
            int ymin = (int)(y + filt.ymin_coef * h);
            int ymax = (int)(y + filt.ymax_coef * h);

            /**< Scale filter to match ROI */
            cv::resize(filter, overlay, cv::Size(w, ymax - ymin),
                   0, 0, cv::INTER_CUBIC);

            /**< Extract ROI from frame */
            Rect roiRect = Rect(x, y + filt.ypos_coef * h, overlay.cols, overlay.rows);
            roi = frame(roiRect);

            /**< Apply overlay over ROI and then over frame */
            transparentOv(&roi, &roi, &overlay);
            roi.copyTo(frame(roiRect));

        }

        imshow("frame", frame);

        /**< Check key pressed */
        char key = (char) waitKey(30);
        // Exit this loop on escape:
        if(key == KEY_QUIT)
            break;
    }   

    return 0;
}

//void transparentOv(){
//    using namespace cv;
//    cv::Mat display_img( src.size(), src.type() );
//    for (int y = 0; y < src.rows; y++)
//    {
//        const cv::Vec3b* src_pixel = src.ptr<cv::Vec3b>(y);
//        const cv::Vec4b* ovl_pixel = overlay.ptr<cv::Vec4b>(y);
//        cv::Vec3b* dst_pixel = display_img.ptr<cv::Vec3b>(y);
//        for (int x = 0; x < src.cols; x++, ++src_pixel, ++ovl_pixel, ++dst_pixel)
//        {
//            double alpha = (*ovl_pixel).val[3] / 255.0;
//            for (int c = 0; c < 3; c++)
//            {
//                (*dst_pixel).val[c] = (uchar) ((*ovl_pixel).val[c] * alpha + (*src_pixel).val[c] * (1.0 -alpha));
//            }
//        }
//}
//
//}

