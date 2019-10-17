#ifndef GAUSSIAN_BLUR_H
#define GAUSSIAN_BLUR_H

#include "blur.h"

class GaussianBlur : public Blur{
public:
    GaussianBlur():Blur(){}
    GaussianBlur(int ksize):Blur(ksize){}

    cv::Mat doImage(cv::Mat img){
        cv::Mat dst;
        cv::GaussianBlur(img, dst, cv::Size(_ksize, _ksize), 0);
        return dst;
    }
};

#endif // GAUSSIAN_BLUR_H
