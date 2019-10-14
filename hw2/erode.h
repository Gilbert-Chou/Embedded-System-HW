#ifndef ERODE_H
#define ERODE_H

#include "image_process.h"

class Erode : public ImageProcess{
public:
    Erode():_ksize(1){}
    Erode(int ksize):_ksize(ksize){}

    cv::Mat doImage(cv::Mat img){
        cv::Mat dst;

        cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(_ksize, _ksize));
        cv::erode(img, dst, element);
        return dst;
    }

    void setKsize(int ksize){
        _ksize = ksize;
    }
private:
    int _ksize;
};

#endif // ERODE_H
