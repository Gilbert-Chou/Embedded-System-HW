#ifndef MEAN_BLUR_H
#define MEAN_BLUR_H

#include "blur.h"

class MeanBlur : public Blur{
public:
    MeanBlur(int ksize):Blur(ksize){}

    cv::Mat doImage(cv::Mat img){
        cv::Mat dst;
        blur(img, dst, cv::Size(_ksize, _ksize));
        return dst;
    }
};

#endif // MEAN_BLUR_H
