#ifndef MORPH_BLACKHAT_H
#define MORPH_BLACKHAT_H

#include "image_process.h"

class MorphBlackhat : public ImageProcess{
public:
    cv::Mat doImage(cv::Mat img){
        cv::Mat dst;
        cv::morphologyEx(img, dst, cv::MORPH_BLACKHAT, cv::Mat(), cv::Point(-1,-1), 2);
        return dst;
    }
};

#endif // MORPH_BLACKHAT_H
