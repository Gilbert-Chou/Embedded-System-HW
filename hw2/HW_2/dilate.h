#ifndef DILATE_H
#define DILATE_H

#include "image_process.h"

class Dilate : public ImageProcess{
public:
    Dilate():_ksize(1){}
    Dilate(int ksize):_ksize(ksize){}

    cv::Mat doImage(cv::Mat img){
        cv::Mat dst;

        cv::Mat element = cv::getStructuringElement(cv::MORPH_RECT, cv::Size(_ksize, _ksize));
        cv::dilate(img, dst, element);
        return dst;
    }

    void setKsize(int ksize){
        _ksize = ksize;
    }
private:
    int _ksize;
};

#endif // DILATE_H
