#include "dialog.h"
#include "ui_dialog.h"
#include "VideoCapture.h"
#include <QFileInfo>



Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}


Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_Capture_clicked()
{
    VideoCapture *v=new VideoCapture();
    if(isStart==false){
        ui->Capture->setText("save");
        isStart=true;
        myShowImage = convertProcess(temimage);
        ui->label_2->setPixmap(QPixmap::fromImage(myShowImage).scaled(this->ui->label_2->size()));
        pi=false;
    }
    else{
        isStart=false;
        ui->Capture->setText("Capture");
        cv::Mat tem=QImage2cvMat(myShowImage);
        myShowImage = myShowImage.scaled(200,150 ,Qt::KeepAspectRatio);
        int num=0;
        QString text = ui->textEdit->toPlainText();
        QString str ;
        while(true){
            str = QString::number(num);
            QFileInfo file("/home/ubuntu/project4/dataset/"+ text+"_"+str+".jpg");
            if(file.exists()==true)
            {
                    num+=1;
            }
            else
                break;
        }
        filename=text+"_"+str;
//        myShowImage.save("/home/ubuntu/project4/dataset/"+ text+"_"+str+".jpg");
    }
}

QImage Dialog::convertProcess(cv::Mat image)
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
void Dialog::add(cv::Mat img){
    temimage=img.clone();
}

cv::Mat Dialog::QImage2cvMat(QImage image)
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
QString Dialog::name(){
    return filename;
}
