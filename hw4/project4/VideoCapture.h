#ifndef VIDEOCAPTURE_H
#define VIDEOCAPTURE_H
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/features2d/features2d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/video.hpp>


class VideoCapture{
public:
    VideoCapture(){}
    cv::Mat display(){
//        cv::VideoCapture *video = new cv::VideoCapture(0);
        cv::VideoCapture video(0); // 開攝影機
        if (!video.isOpened())
        {
            cv::Mat a;
            return a;
        }
        cv::Mat videoFrame;
        video>>videoFrame; //讀Frame
        cv::waitKey(33); //delay
        return videoFrame;
    }

};



#endif // VIDEOCAPTURE_H
