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

/**
 * Filters definition
 */
/* MUSTACHE: below nose */
#define FILTER_MUSTACHE_FNAME "../filters/mustache.png"
#define FILTER_MUSTACHE_WIDTH_OFFSET 0.0f
#define FILTER_MUSTACHE_HEIGHT_OFFSET 0.62f
#define FILTER_MUSTACHE_SCALE_WIDTH 1.0f
#define FILTER_MUSTACHE_SCALE_HEIGHT 0.2f
/* Glasses: eyes */
#define FILTER_GLASSES_FNAME "../filters/glasses.png"
#define FILTER_GLASSES_WIDTH_OFFSET 0.0f
#define FILTER_GLASSES_HEIGHT_OFFSET 0.3f
#define FILTER_GLASSES_SCALE_WIDTH 1.0f
#define FILTER_GLASSES_SCALE_HEIGHT 0.2f
/* Pig nose: nose */
#define FILTER_PIG_FNAME "../filters/pig.png"
#define FILTER_PIG_WIDTH_OFFSET 0.4f
#define FILTER_PIG_HEIGHT_OFFSET 0.5f
#define FILTER_PIG_SCALE_WIDTH 0.25f
#define FILTER_PIG_SCALE_HEIGHT 0.25f

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
    // src: https://stackoverflow.com/a/20958245/17836786
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
    float width_offset_coef;
    float height_offset_coef;
    float scale_width;
    float scale_height;
};
typedef struct img_filter img_filter_t;

void applyFilterOverlay(cv::Mat &frame, cv::Mat &filter, img_filter_t *filt){

    using namespace cv;
    #define FACE_MIN_SIZE 100 /**< face min size (in pixels) */
    #define FACE_MIN_NEIGHBORS 3
    #define FACE_SCALE_FACTOR 1.1
    #define FACE_FLAGS 0
    
    Mat frame_gray, roi;
    Mat overlay = filter.clone();
    std::vector<Rect> faces;
    
    /**< Detect faces and draw them */
    cvtColor( frame, frame_gray, COLOR_BGR2GRAY );
    equalizeHist( frame_gray, frame_gray );
    _face_cascade.detectMultiScale( frame_gray, faces, FACE_SCALE_FACTOR,
                                    FACE_MIN_NEIGHBORS, FACE_FLAGS,
                                    Size(FACE_MIN_SIZE, FACE_MIN_SIZE) );

    for (size_t i = 0; i < faces.size(); i++) {
      // rectangle( frame, faces.at(i), (255, 0, 255), 2);

      int x = faces.at(i).x;
      int y = faces.at(i).y;
      int h = faces.at(i).height;
      int w = faces.at(i).width;
      //int ymin = (int)(y + filt->ymin_coef * h);
      //int ymax = (int)(y + filt->ymax_coef * h);
      ////int xmin = (int)(x + filt->xmin_coef * w);
      ////int xmax = (int)(x + filt->xmax_coef * w);

      //int xrange = (int)(x + (filt->xmax_coef - filt->xmin_coef) * w);
      //int yrange = (int)(y + (filt->ymax_coef - filt->ymin_coef) * h);

      //   /**< Scale filter to match ROI */
      //   cv::resize(*filter, overlay, cv::Size(w, ymax - ymin),
      //              0, 0, cv::INTER_CUBIC);
      // /**< Scale filter to match ROI */
      //cv::resize(filter, overlay,
      //           cv::Size(filt->resize_width * xrange,
      //                    filt->resize_height * yrange),
      //           0, 0, cv::INTER_CUBIC);

      cv::resize(filter, overlay,
                 cv::Size( ((int)(filt->scale_width * w)),
                           ((int)(filt->scale_height * h)) ),
                 0, 0, cv::INTER_CUBIC);


      /**< Extract ROI from frame */
      Rect roiRect = Rect(x + filt->width_offset_coef * w,
                          y + filt->height_offset_coef * h,
                          overlay.cols, overlay.rows);
      roi = frame(roiRect);

      /**< Apply overlay over ROI and then over frame */
      transparentOv(&roi, &roi, &overlay);
      // src: https://stackoverflow.com/a/10482252/17836786
      roi.copyTo(frame(roiRect));
    }
}

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

    //struct img_filter {
    //  std::string name;
    //  float xmin_coef;
    //  float xmax_coef;
    //  float xpos_coef;
    //  float resize_width;
    //  float ymin_coef;
    //  float ymax_coef;
    //  float ypos_coef;
    //  float resize_height;
    //};

//    struct img_filter {
//      std::string name;
//      float width_offset_coef;
//      float height_offset_coef;
//      float scale_width;
//      float scale_height;
//    };

    img_filter_t filt_mustache = {
        // below nose
        FILTER_MUSTACHE_FNAME,
        FILTER_MUSTACHE_WIDTH_OFFSET, FILTER_MUSTACHE_HEIGHT_OFFSET,
        FILTER_MUSTACHE_SCALE_WIDTH, FILTER_MUSTACHE_SCALE_HEIGHT
    };

    img_filter_t filt_glasses = {
        // eyes
        FILTER_GLASSES_FNAME,
        FILTER_GLASSES_WIDTH_OFFSET, FILTER_GLASSES_HEIGHT_OFFSET,
        FILTER_GLASSES_SCALE_WIDTH, FILTER_GLASSES_SCALE_HEIGHT
    };

    img_filter_t filt_pig = {
        // nose
        FILTER_PIG_FNAME,
        FILTER_PIG_WIDTH_OFFSET, FILTER_PIG_HEIGHT_OFFSET,
        FILTER_PIG_SCALE_WIDTH, FILTER_PIG_SCALE_HEIGHT
    };

    std::vector<img_filter_t> filters;
    filters.push_back(filt_mustache);
    filters.push_back(filt_glasses);
    filters.push_back(filt_pig);

    int filter_idx = 2;

    /**< Get filter */
    Mat filter = imread(filters.at(filter_idx).name, -1); // 4-channel BGRA
    //Mat filter = imread(FILTER_FNAME); // 3-channel BGR
    if( filter.empty() ){
        cerr << "Error opening the filter!" << endl;
        return -1;
    }

    //cv::resize(image,image, Size(WIDTH, HEIGHT) );

    Mat frame, frame_gray, roi;
    for(;;){
        cap >> frame;

        applyFilterOverlay(frame, filter, &filters.at(filter_idx));

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

