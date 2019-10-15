#ifndef MORPH_GRADIENT_H
#define MORPH_GRADIENT_H

#include "image_process.h"

class MorphGradient : public ImageProcess{
public:
    cv::Mat doImage(cv::Mat img){
        cv::Mat dst;
        cv::morphologyEx(img, dst, cv::MORPH_GRADIENT, cv::Mat(), cv::Point(-1,-1), 2);
        return dst;
    }
};

#endif // MORPH_GRADIENT_H
