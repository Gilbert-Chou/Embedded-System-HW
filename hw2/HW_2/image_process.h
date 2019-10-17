#ifndef IMAGE_PROCESS_H
#define IMAGE_PROCESS_H
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

class ImageProcess{
public:
    virtual cv::Mat doImage(cv::Mat img) = 0;
};

#endif // IMAGE_PROCESS_H
