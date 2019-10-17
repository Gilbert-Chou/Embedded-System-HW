#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QImage>
#include <QPixmap>
#include <QFileDialog>
#include "image_process.h"
#include "morph_blackhat.h"
#include "threshold.h"
#include "gray.h"
#include "eq_hist.h"
#include "mean_blur.h"
#include "median_blur.h"
#include "gaussian_blur.h"
#include "bilateral_blur.h"
#include "dilate.h"
#include "erode.h"
#include "morph_open.h"
#include "morph_close.h"
#include "morph_gradient.h"
#include "morph_tophat.h"
#include "morph_blackhat.h"

#include <time.h>

MainWindow::MainWindow(QWidget *parent) :

    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    _original_image = cv::imread("/home/ubuntu/Embedded-System-HW/hw2/Images/board.jpg");
//    QImage myShowImage;
//    myShowImage = convertProcess(_original_image);
//    ui->uiImg1->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->uiImg1->size()));
//    cv::Mat img_gray;
//    img_gray = _ip->doImage(img1);
//    QImage Img2 = convertProcess(img_gray);
//    ui->uiImg2->setPixmap(QPixmap::fromImage(Img2).scaled(this->ui->uiImg2->size()));

//    cv::imshow("Ori", img);
//    _ip = new Threshold(true);
//    img = _ip->doImage(img);
//    cv::imshow("Test", img);
//    delete _ip;
//    _ip = new Dilate(3);
//    img = _ip->doImage(img);
//    cv::imshow("Test2", img);
//    delete _ip;
//    _ip = new MorphBlackhat();
//    cv::imshow("Test3", _ip->doImage(img));


}


QImage MainWindow::convertProcess(cv::Mat img){
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



MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_open_button_clicked()
{
   start=(double)clock();
   QString path = QFileDialog::getOpenFileName(this, tr("Open Image"), ".", tr("Image Files(*.jpg *.png *.bmp)"));
   std::string newpath=std::string((const char *)path.toLocal8Bit());
   cv::Mat image=cv::imread(newpath);
   image.copyTo(_original_image);
   QImage myShowImage;
   myShowImage = convertProcess(image);
   ui->uiImg1->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->uiImg1->size()));
   ui->uiImg2->setText("Gray Image");
   _gray_image.release();
   ui->uiImg3->setText("Denoise Image");
   _denoise_image.release();
   ui->uiImg4->setText("Threshold Image");
   _threshold_image.release();
   ui->uiImg5->setText("Morphology Image");
   _morphology_image.release();
   end=(double)clock();
   time=end-start;
   QString str = QString::number(time)+"ms";
   ui->time_label->setText(str);
}

void MainWindow::on_clear_button_clicked()
{
    start=(double)clock();
    ui->uiImg1->setText("Original Image");
    _original_image.release();
    ui->uiImg2->setText("Gray Image");
    _gray_image.release();
    ui->uiImg3->setText("Denoise Image");
    _denoise_image.release();
    ui->uiImg4->setText("Threshold Image");
    _threshold_image.release();
    ui->uiImg5->setText("Morphology Image");
    _morphology_image.release();
    end=(double)clock();
    time=end-start;
    QString str = QString::number(time)+"ms";
    ui->time_label->setText(str);
}

void MainWindow::on_close_button_clicked()
{
    exit(0);
}

void MainWindow::on_gray_button_clicked()
{
    if(!_original_image.empty())
    {
        start=(double)clock();
        _ip = new Gray();
        _gray_image=_ip->doImage(_original_image);
        QImage myShowImage;
        myShowImage = convertProcess(_gray_image);
        ui->uiImg2->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->uiImg2->size()));
        ui->uiImg3->setText("Denoise Image");
        _denoise_image.release();
        ui->uiImg4->setText("Threshold Image");
        _threshold_image.release();
        ui->uiImg5->setText("Morphology Image");
        _morphology_image.release();
        end=(double)clock();
        time=end-start;
        QString str = QString::number(time)+"ms";
        ui->time_label->setText(str);
    }
}

void MainWindow::on_eqhist_button_clicked()
{
    if(!_original_image.empty())
    {
        start=(double)clock();
        _ip = new EqHist();
        _gray_image=_ip->doImage(_original_image);
        QImage myShowImage;
        myShowImage = convertProcess(_gray_image);
        ui->uiImg2->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->uiImg2->size()));
        ui->uiImg3->setText("Denoise Image");
        _denoise_image.release();
        ui->uiImg4->setText("Threshold Image");
        _threshold_image.release();
        ui->uiImg5->setText("Morphology Image");
        _morphology_image.release();
        end=(double)clock();
        time=end-start;
        QString str = QString::number(time)+"ms";
        ui->time_label->setText(str);
    }
}

void MainWindow::on_blur_button_clicked()
{
    if (!_gray_image.empty())
    {
        start=(double)clock();
        _ip = new MeanBlur(3);
        _denoise_image=_ip->doImage(_gray_image);
        QImage myShowImage;
        myShowImage = convertProcess(_denoise_image);
        ui->uiImg3->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->uiImg3->size()));
        ui->uiImg4->setText("Threshold Image");
        _threshold_image.release();
        ui->uiImg5->setText("Morphology Image");
        _morphology_image.release();
        end=(double)clock();
        time=end-start;
        QString str = QString::number(time)+"ms";
        ui->time_label->setText(str);
    }
}


void MainWindow::on_median_blur_button_clicked()
{
    if (!_gray_image.empty())
    {
        start=(double)clock();
        _ip = new MedianBlur(3);
        _denoise_image=_ip->doImage(_gray_image);
        QImage myShowImage;
        myShowImage = convertProcess(_denoise_image);
        ui->uiImg3->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->uiImg3->size()));
        ui->uiImg4->setText("Threshold Image");
        _threshold_image.release();
        ui->uiImg5->setText("Morphology Image");
        _morphology_image.release();
        end=(double)clock();
        time=end-start;
        QString str = QString::number(time)+"ms";
        ui->time_label->setText(str);
    }
}


void MainWindow::on_gaussian_blur_button_clicked()
{
    if (!_gray_image.empty())
    {
        start=(double)clock();
        _ip = new GaussianBlur(3);
        _denoise_image=_ip->doImage(_gray_image);
        QImage myShowImage;
        myShowImage = convertProcess(_denoise_image);
        ui->uiImg3->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->uiImg3->size()));
        ui->uiImg4->setText("Threshold Image");
        _threshold_image.release();
        ui->uiImg5->setText("Morphology Image");
        _morphology_image.release();
        end=(double)clock();
        time=end-start;
        QString str = QString::number(time)+"ms";
        ui->time_label->setText(str);
    }
}

void MainWindow::on_bilateral_blur_button_clicked()
{
    if (!_gray_image.empty())
    {
        start=(double)clock();
        _ip = new BilateralBlur(3);
        _denoise_image=_ip->doImage(_gray_image);
        QImage myShowImage;
        myShowImage = convertProcess(_denoise_image);
        ui->uiImg3->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->uiImg3->size()));
        ui->uiImg4->setText("Threshold Image");
        _threshold_image.release();
        ui->uiImg5->setText("Morphology Image");
        _morphology_image.release();
        end=(double)clock();
        time=end-start;
        QString str = QString::number(time)+"ms";
        ui->time_label->setText(str);
    }
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    int number = ui->lineEdit->text().toInt();

    if (number < 0)
    {
        ui->lineEdit->setText("0");
    }
    else if (number > 255)
    {
        ui->lineEdit->setText("255");
    }
}

void MainWindow::on_threshold_button_clicked()
{
    if (!_denoise_image.empty())
    {
        start=(double)clock();
        int number = ui->lineEdit->text().toInt();
        _ip = new Threshold(number);
        _threshold_image = _ip->doImage(_denoise_image);
        QImage myShowImage;
        myShowImage = convertProcess(_threshold_image);
        ui->uiImg4->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->uiImg4->size()));
        ui->uiImg5->setText("Morphology Image");
        _morphology_image.release();
        end=(double)clock();
        time=end-start;
        QString str = QString::number(time)+"ms";
        ui->time_label->setText(str);
    }
}

void MainWindow::on_threshold_otsu_button_clicked()
{
    if (!_denoise_image.empty())
    {
        start=(double)clock();
        _ip = new Threshold(true);
        _threshold_image = _ip->doImage(_denoise_image);
        QImage myShowImage;
        myShowImage = convertProcess(_threshold_image);
        ui->uiImg4->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->uiImg4->size()));
        ui->uiImg5->setText("Morphology Image");
        _morphology_image.release();
        end=(double)clock();
        time=end-start;
        QString str = QString::number(time)+"ms";
        ui->time_label->setText(str);
    }
}

void MainWindow::on_dilate_button_clicked()
{
    if (!_threshold_image.empty())
    {
        start=(double)clock();
        _ip = new Dilate(3);
        _morphology_image = _ip->doImage(_threshold_image);
        QImage myShowImage;
        myShowImage = convertProcess(_morphology_image);
        ui->uiImg5->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->uiImg5->size()));
        end=(double)clock();
        time=end-start;
        QString str = QString::number(time)+"ms";
        ui->time_label->setText(str);
    }
}

void MainWindow::on_erode_button_clicked()
{
    if (!_threshold_image.empty())
    {
        start=(double)clock();
        _ip = new Erode(3);
        _morphology_image = _ip->doImage(_threshold_image);
        QImage myShowImage;
        myShowImage = convertProcess(_morphology_image);
        ui->uiImg5->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->uiImg5->size()));
        end=(double)clock();
        time=end-start;
        QString str = QString::number(time)+"ms";
        ui->time_label->setText(str);
    }
}

void MainWindow::on_morph_open_button_clicked()
{
    if (!_threshold_image.empty())
    {
        start=(double)clock();
        _ip = new MorphOpen();
        _morphology_image = _ip->doImage(_threshold_image);
        QImage myShowImage;
        myShowImage = convertProcess(_morphology_image);
        ui->uiImg5->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->uiImg5->size()));
        end=(double)clock();
        time=end-start;
        QString str = QString::number(time)+"ms";
        ui->time_label->setText(str);
    }
}

void MainWindow::on_morph_closing_button_clicked()
{
    if (!_threshold_image.empty())
    {
        start=(double)clock();
        _ip = new MorphClose();
        _morphology_image = _ip->doImage(_threshold_image);
        QImage myShowImage;
        myShowImage = convertProcess(_morphology_image);
        ui->uiImg5->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->uiImg5->size()));
        end=(double)clock();
        time=end-start;
        QString str = QString::number(time)+"ms";
        ui->time_label->setText(str);
    }
}

void MainWindow::on_morph_gradient_button_clicked()
{
    if (!_threshold_image.empty())
    {
        start=(double)clock();
        _ip = new MorphGradient();
        _morphology_image = _ip->doImage(_threshold_image);
        QImage myShowImage;
        myShowImage = convertProcess(_morphology_image);
        ui->uiImg5->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->uiImg5->size()));
        end=(double)clock();
        time=end-start;
        QString str = QString::number(time)+"ms";
        ui->time_label->setText(str);
    }
}

void MainWindow::on_morph_tophat_button_clicked()
{
    if (!_threshold_image.empty())
    {
        start=(double)clock();
        _ip = new MorphTophat();
        _morphology_image = _ip->doImage(_threshold_image);
        QImage myShowImage;
        myShowImage = convertProcess(_morphology_image);
        ui->uiImg5->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->uiImg5->size()));
        end=(double)clock();
        time=end-start;
        QString str = QString::number(time)+"ms";
        ui->time_label->setText(str);
    }
}

void MainWindow::on_morph_blackhat_button_clicked()
{
    if (!_threshold_image.empty())
    {
        start=(double)clock();
        _ip = new MorphBlackhat();
        _morphology_image = _ip->doImage(_threshold_image);
        QImage myShowImage;
        myShowImage = convertProcess(_morphology_image);
        ui->uiImg5->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->uiImg5->size()));
        end=(double)clock();
        time=end-start;
        QString str = QString::number(time)+"ms";
        ui->time_label->setText(str);
    }
}






