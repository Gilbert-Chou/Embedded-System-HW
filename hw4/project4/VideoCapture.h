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
    cv::Mat facedetectdrow(cv::Mat img,bool issave,QString filename){

        cv::CascadeClassifier faceCascade;
        faceCascade.load("/home/ubuntu/project4/haarcascades/haarcascade_frontalface_alt2.xml");   //加载分类器，注意文件路径


            cv::Mat imgGray;
            std::vector<cv::Rect> faces;

            if (img.channels() == 3)
            {
                cvtColor(img, imgGray, CV_RGB2GRAY);
            }
            else
            {
                imgGray = img;
            }

            faceCascade.detectMultiScale(imgGray, faces, 1.2, 2, 0, cv::Size(0, 0));   //检测人脸

            if (faces.size() > 0)
            {
                for (int i = 0; i < faces.size(); i++)
                {
                    if(issave==true){
                        cv::Mat tem2=img.clone();
                        cv::Rect rect(faces[i].x,faces[i].y, faces[i].width,faces[i].height);
                        cv::Mat image_roi = tem2(rect);
                        cv::resize(image_roi, image_roi, cv::Size(50, 50));
                        QImage aa;
                        aa=convertProcess(image_roi);
                        aa.save("/home/ubuntu/project4/dataset/"+filename+".jpg");
                    }
                    rectangle(img, cv::Point(faces[i].x, faces[i].y), cv::Point(faces[i].x + faces[i].width, faces[i].y + faces[i].height),
                        cv::Scalar(0, 255, 0), 1, 8);    //框出人脸位置
                }
                facessize=faces.size();
            }
            return img;
    }
    QImage convertProcess(cv::Mat image)
    {
        if(image.type()==CV_8UC1)
        {
            return QImage((unsigned char *)image.data,image.cols,image.rows,image.step,QImage::Format_Indexed8).copy();
        }
        else
        {
            cv::Mat dst;
            image.copyTo(dst);
            cv::cvtColor(image,dst,CV_BGR2RGB);
            return QImage((unsigned char *)dst.data,dst.cols,dst.rows,dst.step,QImage::Format_RGB888).copy();
        }
    }
    int getfacesize(){
        return facessize;
    }
private:
    int facessize=0;
};



#endif // VIDEOCAPTURE_H
