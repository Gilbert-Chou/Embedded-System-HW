#ifndef MEDIAN_BLUR_H
#define MEDIAN_BLUR_H

#include "blur.h"

class MedianBlur : public Blur{
public:
    MedianBlur():Blur(){}
    MedianBlur(int ksize):Blur(ksize){}

    cv::Mat doImage(cv::Mat img){
        cv::Mat dst;
        cv::medianBlur(img, dst, _ksize);
        return dst;
    }
};
#endif // MEDIAN_BLUR_H
