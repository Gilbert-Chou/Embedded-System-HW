#ifndef IMAGE_PROCESS_H
#define IMAGE_PROCESS_H
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QImage>
#include <QPixmap>

class ImageProcess{
public:
    virtual cv::Mat doImage(cv::Mat img) = 0;
    QImage convertProcess(cv::Mat img){
        if(img.type() == CV_8UC1){
            return QImage((unsigned char*)img.data, img.cols, img.rows, img.step, QImage::Format_Indexed8);
        }
        else{
            cv::Mat dst;
            cvtColor(img, dst, CV_BGR2RGB);
            return QImage((unsigned char*)dst.data, dst.cols, dst.rows, dst.step, QImage::Format_RGB888);
        }
    }
};

#endif // IMAGE_PROCESS_H
