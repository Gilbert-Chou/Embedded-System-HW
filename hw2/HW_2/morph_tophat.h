#ifndef MORPH_TOPHAT_H
#define MORPH_TOPHAT_H

#include "image_process.h"

class MorphTophat : public ImageProcess{
public:
    cv::Mat doImage(cv::Mat img){
        cv::Mat dst;
        cv::morphologyEx(img, dst, cv::MORPH_TOPHAT, cv::Mat(), cv::Point(-1,-1), 2);
        return dst;
    }
};

#endif // MORPH_TOPHAT_H
