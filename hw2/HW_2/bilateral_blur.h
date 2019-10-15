#ifndef BILATERAL_BLUR_H
#define BILATERAL_BLUR_H

#include "blur.h"

class BilateralBlur : public Blur{
public:
    BilateralBlur(int ksize):Blur(ksize){}

    cv::Mat doImage(cv::Mat img){
        cv::Mat dst;
        cv::bilateralFilter(img, dst, _ksize, _ksize*2, _ksize/2.0);
        return dst;
    }
};

#endif // BILATERAL_BLUR_H
