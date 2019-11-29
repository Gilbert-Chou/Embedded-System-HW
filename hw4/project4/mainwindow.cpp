#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "VideoCapture.h"
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d.hpp"

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

cv::Mat MainWindow::QImage2cvMat(QImage image)
{
    cv::Mat mat;
    switch(image.format())
    {
    case QImage::Format_ARGB32:
    case QImage::Format_RGB32:
    case QImage::Format_ARGB32_Premultiplied:
        mat = cv::Mat(image.height(), image.width(), CV_8UC4, (void*)image.constBits(), image.bytesPerLine());
        break;
    case QImage::Format_RGB888:
        mat = cv::Mat(image.height(), image.width(), CV_8UC3, (void*)image.constBits(), image.bytesPerLine());
        cv::cvtColor(mat, mat, CV_BGR2RGB);
        break;
    case QImage::Format_Indexed8:
        mat = cv::Mat(image.height(), image.width(), CV_8UC1, (void*)image.constBits(), image.bytesPerLine());
        break;
    }
    return mat;
}


int MainWindow::trainModel(){
//    圖片要200*150
        std::vector<cv::Mat> images;
        std::vector<int> labels;
        // images for first person
        images.push_back(cv::imread("/home/ubuntu/project4/dataset/1.jpg", CV_LOAD_IMAGE_GRAYSCALE));
        labels.push_back(0);
        images.push_back(cv::imread("/home/ubuntu/project4/dataset/2.jpg", CV_LOAD_IMAGE_GRAYSCALE));
        labels.push_back(0);
        images.push_back(cv::imread("/home/ubuntu/project4/dataset/3.jpg", CV_LOAD_IMAGE_GRAYSCALE));
        labels.push_back(0);

        // images for second person
        images.push_back(cv::imread("/home/ubuntu/project4/dataset/5.jpg", CV_LOAD_IMAGE_GRAYSCALE));
        labels.push_back(1);
        images.push_back(cv::imread("/home/ubuntu/project4/dataset/4.jpg", CV_LOAD_IMAGE_GRAYSCALE));
        labels.push_back(1);
        cv::Ptr<cv::FaceRecognizer> model = cv::createFisherFaceRecognizer();
        //訓練
        model->train(images, labels);
        cv::Mat img = cv::imread("/home/ubuntu/project4/test.jpg", CV_LOAD_IMAGE_GRAYSCALE);
        //測試
        int predicted = model->predict(img);
        return predicted;
}


void MainWindow::on_Face_clicked()
{
    facedetect=myShowImage;
    ui->Detect->setPixmap(QPixmap::fromImage(facedetect).scaled(400,300,Qt::KeepAspectRatio));
    facedetect = facedetect.scaled(200,150 ,Qt::KeepAspectRatio);
    facedetect.save("/home/ubuntu/project4/test.jpg");

//    cv::Mat ee;
//    ee=QImage2cvMat(facedetect);
    int predict;
    predict=trainModel();
    QString str = QString::number(predict);
    ui->peopletext->setText(str);
    if (predict==0){
       ui->nametext->setText("107598012");
    }
    else if (predict==1){
       ui->nametext->setText("107598042");
    }



}

void MainWindow::on_Addface_clicked()
{
   pi=true;
   Dialog D;
   D.add(ttttt);
   D.setModal(true);
   D.exec();
}

