#ifndef MEDIAN_BLUR_H
#define MEDIAN_BLUR_H

#include "blur.h"

class MedianBlur : public Blur{
public:
    MedianBlur(int ksize):Blur(ksize){}

    cv::Mat doImage(cv::Mat img){
        cv::Mat dst;
        medianBlur(img, dst, _ksize);
        return dst;
    }
};
#endif // MEDIAN_BLUR_H
