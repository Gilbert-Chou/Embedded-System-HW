#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "QImage"
#include "QPixmap"
namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();
    void add(cv::Mat img);
    cv::Mat QImage2cvMat(QImage image);
    QString name();
private slots:
    void on_Capture_clicked();

private:
    Ui::Dialog *ui;
    QImage myShowImage;
    QImage facedetect;
    QImage convertProcess(cv::Mat image);
    bool isStart =false;
    bool pi=false;
    cv::Mat temimage;
    QString filename;
};

#endif // DIALOG_H
