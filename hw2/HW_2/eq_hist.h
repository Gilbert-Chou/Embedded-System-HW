#ifndef EQ_HIST_H
#define EQ_HIST_H

#include "image_process.h"

class EqHist : public ImageProcess{
public:
    cv::Mat doImage(cv::Mat img){
        cv::Mat dst;
        cv::equalizeHist(img, dst);
        return dst;
    }
};

#endif // EQ_HIST_H
