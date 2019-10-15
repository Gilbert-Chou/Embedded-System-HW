#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <QImage>
#include <QPixmap>
#include "image_process.h"
#include "dilate.h"
#include "morph_blackhat.h"
#include "threshold.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    cv::Mat img = cv::imread("../img/board.jpg", CV_8UC1);
    cv::imshow("Ori", img);
    _ip = new Threshold(true);
    img = _ip->doImage(img);
    cv::imshow("Test", img);
    delete _ip;
    _ip = new Dilate(3);
    img = _ip->doImage(img);
    cv::imshow("Test2", img);
    delete _ip;
    _ip = new MorphBlackhat();
    cv::imshow("Test3", _ip->doImage(img));
    ui->setupUi(this);

}

MainWindow::~MainWindow()
{
    delete ui;
}

