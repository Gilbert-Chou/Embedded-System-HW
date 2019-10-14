#ifndef MORPH_CLOSE_H
#define MORPH_CLOSE_H

#include "image_process.h"

class MorphClose : public ImageProcess{
public:
    cv::Mat doImage(cv::Mat img){
        cv::Mat dst;
        cv::morphologyEx(img, dst, cv::MORPH_CLOSE, cv::Mat(), cv::Point(-1,-1), 2);
        return dst;
    }
};

#endif // MORPH_CLOSE_H
