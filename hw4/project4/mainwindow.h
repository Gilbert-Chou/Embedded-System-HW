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
    QImage convertProcess(cv::Mat image);
    int trainModel();
    cv::Mat QImage2cvMat(QImage image);
    void removeListSame(QStringList *list);
private slots:
    void on_CloseApp_clicked();

    void on_open_clicked();
    void on_Face_clicked();

    void on_Addface_clicked();
    void display(QImage);
private:
    Ui::MainWindow *ui;
    QImage myShowImage;
    QImage facedetect;
    bool isStart = false;
    bool flag=true;
    bool pi=true;
};

#endif // MAINWINDOW_H
