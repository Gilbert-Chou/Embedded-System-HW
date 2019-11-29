#include "mainwindow.h"
#include <QApplication>
#include "Thread.h"
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "Thread.h"
#include <QPixmap>
#include "dialog.h"
#include "iostream"
#include <vector>
int main(int argc, char *argv[])
{
//    std::vector<cv::Mat> images;
//    std::vector<int> labels;
//    // images for first person
//    images.push_back(cv::imread("0.jpg", CV_LOAD_IMAGE_GRAYSCALE));
//    labels.push_back(0);
//    images.push_back(cv::imread("/home/ubuntu/project4/1.jpg", CV_LOAD_IMAGE_GRAYSCALE));
//    labels.push_back(0);
//    // images for second person
//    images.push_back(cv::imread("/home/ubuntu/project4/3.jpg", CV_LOAD_IMAGE_GRAYSCALE));
//    labels.push_back(1);
//    images.push_back(cv::imread("/home/ubuntu/project4/4.jpg", CV_LOAD_IMAGE_GRAYSCALE));
//    labels.push_back(1);
//    cv::Ptr<cv::FaceRecognizer> model = cv::createFisherFaceRecognizer();
//    //訓練
//    model->train(images, labels);
//    cv::Mat img = cv::imread("/home/ubuntu/project4/5.jpg", CV_LOAD_IMAGE_GRAYSCALE);
//    //測試
//    int predicted = model->predict(img);
//    std::cout<<predicted;



        QApplication a(argc, argv);
        MainWindow w;

        w.show();

       return a.exec();
}
