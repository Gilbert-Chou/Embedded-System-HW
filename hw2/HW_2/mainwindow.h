#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "image_process.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    QImage convertProcess(cv::Mat img);
    ~MainWindow();

private slots:
    void on_gray_button_clicked();

    void on_eqhist_button_clicked();

    void on_blur_button_clicked();


    void on_median_blur_button_clicked();

    void on_open_button_clicked();

    void on_gaussian_blur_button_clicked();

    void on_bilateral_blur_button_clicked();

    void on_threshold_button_clicked();

    void on_threshold_otsu_button_clicked();

    void on_dilate_button_clicked();

    void on_erode_button_clicked();

    void on_morph_open_button_clicked();

    void on_morph_closing_button_clicked();

    void on_morph_gradient_button_clicked();

    void on_morph_tophat_button_clicked();

    void on_morph_blackhat_button_clicked();

    void on_clear_button_clicked();

    void on_lineEdit_textChanged(const QString &arg1);

    void on_close_button_clicked();

private:
    Ui::MainWindow *ui;
    ImageProcess *_ip;
    cv::Mat _original_image;
    cv::Mat _gray_image;
    cv::Mat _denoise_image;
    cv::Mat _threshold_image;
    cv::Mat _morphology_image;
//    QImage convertProcess(cv::Mat image);
    double start,end,time;

};

#endif // MAINWINDOW_H
