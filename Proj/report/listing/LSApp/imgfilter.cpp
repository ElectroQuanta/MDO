#include "imgfilter.h"
#include <opencv2/imgcodecs.hpp> /**< for imread */

//ImgFilter::ImgFilter(){}

ImgFilter::ImgFilter(std::string path,
                     float width_offset_coef = 0.0,
                     float height_offset_coef = 0.0,
                     float scale_width = 1.0,
                     float scale_height = 1.0){
    /**< Check inconsistencies */
    if(
        (scale_width > 1.0 || scale_width < 0.0) ||
        (scale_height > 1.0 || scale_height < 0.0) ||
        (width_offset_coef > 1.0 || width_offset_coef < 0.0) ||
        (height_offset_coef > 1.0 || height_offset_coef < 0.0)
        ){
        _empty = true;
        return;
    }

    /**< Build img filter */
    _width_offset_coef = width_offset_coef;
    _height_offset_coef = height_offset_coef;
    _scale_width = scale_width;
    _scale_height = scale_height;

    using namespace cv;
    _filter = imread(path, -1); // 4-channel BGRA
    _empty = _filter.empty();
}

//const cv::Mat &ImgFilter::Mat() { return _filter; }

//bool ImgFilter::open(){
//    using namespace cv;
//    Mat filter = imread(_name, -1); // 4-channel BGRA
//    //Mat filter = imread(FILTER_FNAME); // 3-channel BGR
//    
//    _empty = filter.empty();
//
//    return _empty;
//}

