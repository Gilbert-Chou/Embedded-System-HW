#ifndef GRAY_H
#define GRAY_H
#include "image_process.h"

class Gray : public ImageProcess{
public:
    cv::Mat doImage(cv::Mat img){
        cv::Mat dst;
        cv::cvtColor(img, dst, CV_BGR2GRAY);
        return dst;
    }
};

#endif // GRAY_H
