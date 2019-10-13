#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QImage>
#include <QPixmap>
#include "image_process.h"
#include "threshold.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    cv::Mat img = cv::imread("../img/board.jpg", CV_8UC1);
    cv::imshow("Ori", img);
    _ip = new Threshold(true);
    cv::imshow("Test", _ip->doImage(img));
    ((Threshold*)_ip)->setOtsu(false);
    ((Threshold*)_ip)-> setVal(180);
    cv::imshow("Test2", _ip->doImage(img));
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

