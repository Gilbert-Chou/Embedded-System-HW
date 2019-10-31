#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector>
#include <opencv2/opencv.hpp>
#include <opencv2/core/mat.hpp>
#include <string>
#include <QMainWindow>
#define label_init 100
class HoughSeeker{
public:
    cv::Mat findBy(const cv::Mat &input,std::string shape)
    {

        cv::Mat src;
        cv::cvtColor(input, src, CV_BGR2GRAY);
        cv::Mat dst = input.clone();
        cv::Mat temp;
        cv::Mat object = cv::Mat::zeros(src.rows, src.cols, src.type()); //連通物件結構的bounding box
        cv::Rect compRect[255];
        int label_num = label_init;
        //物件計數索引
        int comp_idx = 0;
        //物件弧度變數
        //float ratio[255];
        //物件弧度臨界值
        float ratio_cir_thr1 = 1.0, ratio_cir_thr2 = 0.8;
        float ratio_rec_thr1 = 0.8, ratio_rec_thr2 = 0.75;
        float ratio_tri_thr = 0.6;

        //進行臨界值處理, 將影像二值化
        cv::threshold(src, temp, 0, 255, cv::THRESH_BINARY | cv::THRESH_OTSU);
        //將二值化影像複製到pObject空間
        object = temp.clone();
        for (int i = 0; i < object.rows; i++) {
            for (int j = 0; j < object.cols; j++) {
                cv::Scalar color = object.at<uchar>( cv::Point(j, i));
                if (color.val[0] == 255) { //表示為前景物件像素
                    //取得連通物件資料, 包含物件面積, 座標及寬高, 並給予指定標籤數值
                    floodFill(object,  cv::Point(j, i),  cv::Scalar(label_num), &compRect[comp_idx]);
                    label_num++;
                    comp_idx++;
                }

            }
        }
        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;
        //由二值影像進行輪廓擷取, 並取得輪廓長度
        cv::findContours(temp, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
        //計算物件特徵, 顯示物件面積, 輪廓長度以及弧度值
        for (int i = comp_idx - 1; i >= 0; i--)
        {
            float parameter = arcLength(contours[i], true);
            //物體弧度：e = 4π(面積)/(周長)2
            float tempR = 4 * CV_PI * contourArea(contours[i]) / (parameter * parameter);

            std::cout<< tempR <<std::endl;

            if (shape=="circle")
            {
                if(tempR<ratio_cir_thr1 && tempR>ratio_cir_thr2)
                {
                    cv::Scalar color = cv::Scalar(255, 255, 255);
                    cv::drawContours(dst, contours, i, color, 2, 8, hierarchy);
                }
            }
            if (shape=="squre")
            {
                if(tempR<ratio_rec_thr1 && tempR>ratio_rec_thr2)
                {
                    cv::Scalar color = cv::Scalar(255, 255, 255);
                    cv::drawContours(dst, contours, i, color, 2, 8, hierarchy);
                }

            }

            if (shape=="triangle")
            {
                if(tempR<ratio_tri_thr)
                {
                    cv::Scalar color = cv::Scalar(255, 255, 255);
                    cv::drawContours(dst, contours, i, color, 2, 8, hierarchy);
                }

            }
        }

        cv::resize(dst, dst, cv::Size(400, 300));
        return dst;
    }




    QImage findContours(const cv::Mat &input)
    {
        cv::Mat src = input;
        cv::Mat contoursImg = src.clone();
        cv::Mat edge;
        cv::blur(src, src, cv::Size(3,3));
        cv::Canny(src, edge, 50, 150, 3);
        std::vector<std::vector<cv::Point> > contours;
        std::vector<cv::Vec4i> hierarchy;
        cv::RNG rng(12345);
        //找輪廓
        cv::findContours(edge, contours, hierarchy, CV_RETR_TREE, CV_CHAIN_APPROX_NONE);
        for(int i = 0; i<contours.size(); i++)
        {
            cv::Scalar color = cv::Scalar( rng.uniform(0, 255), rng.uniform(0, 255), 255);
            //畫輪廓
            drawContours(contoursImg, contours, i, color, 2, 8, hierarchy);
        }
        return this->convertProcess(contoursImg);
    }

    QImage seekCircle(const cv::Mat &input)
    {
       return  this->convertProcess(this->findBy(input,"circle"));
    }

    QImage seekTriangle(const cv::Mat &input)
    {
       return  this->convertProcess(this->findBy(input,"triangle"));
    }

    QImage seekSqure(const cv::Mat &input)
    {

       return  this->convertProcess(this->findBy(input,"squre"));
    }

    QImage convertProcess(cv::Mat img){
        if(img.type() == CV_8UC1){
            return QImage((unsigned char*)img.data, img.cols, img.rows, img.step, QImage::Format_Indexed8).copy();
        }
        else{
            cv::Mat dst;
            img.copyTo(dst);
            cv::cvtColor(dst, dst, CV_BGR2RGB);
            return QImage((unsigned char*)dst.data, dst.cols, dst.rows, dst.step, QImage::Format_RGB888).copy();
        }
    }


};
#endif // PROCESSOR_H
