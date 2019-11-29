#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "VideoCapture.h"
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "Thread.h"
#include <QPixmap>
#include "dialog.h"


Thread *thread1=new Thread();
cv::Mat ttttt;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_CloseApp_clicked()
{
    thread1->stop();
    exit(0);
}

void MainWindow::on_open_clicked()
{
    VideoCapture *v=new VideoCapture();
//    thread1->start();
//    QObject::connect(thread1,SIGNAL(ShowImage(QImage)),this,SLOT(display(QImage)));
    if(flag==true){
        cv::Mat tem;
        flag=false;
        pi=true;
        while(pi){
            tem=v->display();
            ttttt = tem.clone();
            myShowImage = convertProcess(tem);
//            ui->Input->setPixmap(QPixmap::fromImage(myShowImage).scaled(400,300,Qt::KeepAspectRatio));
            ui->Input->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->Input->size()));
        }
    }
}
void MainWindow::display(QImage a){
    ui->Input->setPixmap(QPixmap::fromImage(a).scaled(400,300,Qt::KeepAspectRatio));
}


QImage MainWindow::convertProcess(cv::Mat image)
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

void MainWindow::on_Face_clicked()
{
    facedetect=myShowImage;
    ui->Detect->setPixmap(QPixmap::fromImage(facedetect).scaled(400,300,Qt::KeepAspectRatio));
}

void MainWindow::on_Addface_clicked()
{
   pi=true;
   Dialog D;
   D.add(ttttt);
   D.setModal(true);
   D.exec();
}

