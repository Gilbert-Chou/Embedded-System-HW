#ifndef MORPH_OPEN_H
#define MORPH_OPEN_H

#include "image_process.h"

class MorphOpen : public ImageProcess{
public:
    cv::Mat doImage(cv::Mat img){
        cv::Mat dst;
        cv::morphologyEx(img, dst, cv::MORPH_OPEN, cv::Mat(), cv::Point(-1,-1), 2);
        return dst;
    }
};

#endif // MORPH_OPEN_H
