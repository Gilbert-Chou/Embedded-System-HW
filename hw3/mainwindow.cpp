#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QDebug>
#include <QImage>
#include <QPixmap>
#include <opencv2/core/core.hpp>
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/features2d.hpp"
#include "opencv2/nonfree/nonfree.hpp"
#include "surf.h"
#include "processor.h"
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

void MainWindow::on_openTarget_clicked()
{
      cv::Mat image=loadFromFile();
      if(!image.empty()){
          image.copyTo(_target_image);
          cv::resize(image, image, cv::Size(400, 300));
          QImage myShowImage;
          myShowImage = convertProcess(image);
          ui->label->setPixmap(QPixmap::fromImage(myShowImage).scaled(400,300,Qt::KeepAspectRatio));
      }

}

cv::Mat MainWindow::loadFromFile()
{
    QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg *.png *.bmp)"));
    std::string newpath=std::string((const char *)path.toLocal8Bit());
    cv::Mat image = cv::imread(newpath);

    return image;
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

void MainWindow::on_close_clicked()
{
    exit(0);
}

void MainWindow::on_Find_clicked()
{
    HoughSeeker *a=new HoughSeeker();
    if(!_target_image.empty()){
        QImage myShowImage=a->findContours(_target_image);
        ui->label->setPixmap(QPixmap::fromImage(myShowImage).scaled(400,300,Qt::KeepAspectRatio));
    }
}

void MainWindow::on_Circle_clicked()
{
    HoughSeeker *a=new HoughSeeker();
    if(!_target_image.empty()){
        QImage myShowImage=a->seekCircle(_target_image.clone());
        ui->label->setPixmap(QPixmap::fromImage(myShowImage).scaled(400,300,Qt::KeepAspectRatio));
    }
}

void MainWindow::on_Triangle_clicked()
{
    HoughSeeker *a=new HoughSeeker();
    if(!_target_image.empty()){
        QImage myShowImage=a->seekTriangle(_target_image.clone());
        ui->label->setPixmap(QPixmap::fromImage(myShowImage).scaled(400,300,Qt::KeepAspectRatio));
    }
}

void MainWindow::on_Rectangle_clicked()
{
    HoughSeeker *a=new HoughSeeker();
    if(!_target_image.empty()){
        QImage myShowImage=a->seekSqure(_target_image.clone());
        ui->label->setPixmap(QPixmap::fromImage(myShowImage).scaled(400,300,Qt::KeepAspectRatio));
    }
}

void MainWindow::on_SURF_clicked()
{
     Surf *a=new Surf(_template_image);
     QImage display;
     display=a->doImage(_target_image);
     ui->label->setPixmap(QPixmap::fromImage(display).scaled(400,300,Qt::KeepAspectRatio));
}

void MainWindow::on_opentemplate_clicked()
{
    cv::Mat image=loadFromFile();
    if(!image.empty()){
        image.copyTo(_template_image);
        cv::resize(image, image, cv::Size(400, 300));
        QImage myShowImage;
        myShowImage = convertProcess(image);

        ui->label_2->setPixmap(QPixmap::fromImage(myShowImage).scaled(400,300,Qt::KeepAspectRatio));
    }
}
