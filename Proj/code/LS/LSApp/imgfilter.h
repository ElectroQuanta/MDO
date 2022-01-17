#ifndef _IMGFILTER_H_
#define _IMGFILTER_H_

#include <string>
#include <opencv2/core/mat.hpp>

class ImgFilter{

public:
    //ImgFilter();
    ImgFilter(std::string path, float width_offset_coef,
                float height_offset_coef, float scale_width,
                float scale_height);
    //~ImgFilter();

    inline bool isEmpty() const { return _empty; }
    inline float width_offset_coef() const { return _width_offset_coef;}
    inline float height_offset_coef() const { return _height_offset_coef;}
    inline float scale_width() const { return _scale_width;}
    inline float scale_height() const { return _scale_height;}
    inline cv::Mat & Mat() { return _filter; }


    //bool open(std::string name);
private:
    //std::string _name;
    float _width_offset_coef;
    float _height_offset_coef;
    float _scale_width;
    float _scale_height;
    bool _empty;
    cv::Mat _filter;
};


#endif // _IMGFILTER_H__H
