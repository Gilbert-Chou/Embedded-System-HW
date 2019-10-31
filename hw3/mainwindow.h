#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "QImage"
#include "QPixmap"
namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_openTarget_clicked();

    void on_close_clicked();

    void on_Find_clicked();

    void on_Circle_clicked();

    void on_Triangle_clicked();

    void on_Rectangle_clicked();

    void on_SURF_clicked();

    void on_opentemplate_clicked();

private:
    Ui::MainWindow *ui;
    QImage convertProcess(cv::Mat image);
    cv::Mat loadFromFile();
    cv::Mat _target_image;
    cv::Mat _template_image;

};

#endif // MAINWINDOW_H
