#ifndef THRESHOLD_H
#define THRESHOLD_H

#include "image_process.h"

class Threshold : public ImageProcess{
public:
    Threshold():_otsu(false), _val(128){}
    Threshold(int val):_otsu(false), _val(val){}
    Threshold(bool otsu):_otsu(otsu), _val(0){}

    cv::Mat doImage(cv::Mat img){
        cv::Mat dst;
        if(_otsu)
            cv::threshold(img, dst, _val, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);
        else cv::threshold(img, dst, _val, 255, CV_THRESH_BINARY);

        return dst;
    }

    void setOtsu(bool otsu){ _otsu = otsu; }
    void setVal(int val){ _val = val; }

private:
    bool _otsu;
    int _val;
};

#endif // THRESHOLD_H
