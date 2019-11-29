#ifndef THREAD_H
#define THREAD_H
#include <QThread>
#include "mainwindow.h"
#include "VideoCapture.h"
#include "ui_mainwindow.h"
class Thread:public QThread{
    Q_OBJECT
public:
    Thread(){}
    void stop(){
        isStop=true;
    }
protected:
    void run(){
        isStop=false;
        VideoCapture *v=new VideoCapture();
        while(!isStop){
            if(flag==true){
                cv::Mat tem;
                flag=false;
                pi=true;
                tem=v->display();
                imshow("video demo", tem); //顯示
                myShowImage = convertProcess(tem);
                emit ShowImage(myShowImage);

            }
        }
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
signals:
    void ShowImage(QImage);
private:
    bool isStop=false;
    bool flag=true;
    bool pi=true;
    QImage myShowImage;
    QImage facedetect;
};

#endif // THREAD_H
