#ifndef EQ_HIST_H
#define EQ_HIST_H

#include "image_process.h"
#include <iostream>

class EqHist : public ImageProcess{
public:
    cv::Mat doImage(cv::Mat img){
        cv::Mat dst;

        if(img.channels() == 3){
//            std::vector<cv::Mat> channels;
//            cv::split(img, channels);

//            cv::Mat B,G,R;

//            cv::equalizeHist( channels[0], B );
//            cv::equalizeHist( channels[1], G );
//            cv::equalizeHist( channels[2], R );

//            std::vector<cv::Mat> combined;
//            combined.push_back(B);
//            combined.push_back(G);
//            combined.push_back(R);

//            cv::merge(combined, dst);

            cv::cvtColor(img, dst, CV_BGR2GRAY);
            cv::equalizeHist(dst, dst);
        }
        else if(img.channels() == 1)
        {
            cv::cvtColor(img, dst, CV_BGR2GRAY);
            cv::equalizeHist(dst, dst);
        }
        else return img;

        return dst;
    }
};

#endif // EQ_HIST_H
