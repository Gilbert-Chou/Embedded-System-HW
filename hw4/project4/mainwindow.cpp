#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "VideoCapture.h"
#include <opencv2/opencv.hpp>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"


#include "Thread.h"
#include <QPixmap>
#include "dialog.h"
#include <QFileDialog>
#include "iostream"
#include <QDir>

Thread *thread1=new Thread();
cv::Mat ttttt;
QStringList labellist;

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
//    圖片要50*50
        std::vector<cv::Mat> images;
        std::vector<int> labels;


        QDir dir_origin("/home/ubuntu/project4/trainset/");
        dir_origin.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        dir_origin.setSorting(QDir::Size | QDir::Reversed);
        QFileInfoList list_origin = dir_origin.entryInfoList();
        for (int i = 0; i < list_origin.size(); i++) {
            QFileInfo fileInfo = list_origin.at(i);
            QString label=fileInfo.fileName().split("_").at(0);
            std::string filename=fileInfo.fileName().toUtf8().constData();
            images.push_back(cv::imread("/home/ubuntu/project4/trainset/"+filename, CV_LOAD_IMAGE_GRAYSCALE));
            labels.push_back(label.toInt());
        }





        QDir dir("/home/ubuntu/project4/dataset/");
        dir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
        dir.setSorting(QDir::Size | QDir::Reversed);
        QFileInfoList list = dir.entryInfoList();

        bool throwit=true;
        for (int i = 0; i < list.size(); i++) {
            QFileInfo fileInfo = list.at(i);
            QString label=fileInfo.fileName().split("_").at(0);
            throwit=true;
            for(int j=0;j<labellist.size();j++){
                if(labellist.at(j)==label){
                    throwit=false;
                }
            }
            if(throwit==true)
                labellist.append(label);
        }
        for (int i = 0; i < list.size(); i++) {
            QFileInfo fileInfo = list.at(i);
            QString label=fileInfo.fileName().split("_").at(0);
            std::string filename=fileInfo.fileName().toUtf8().constData();

            for(int j=0;j<labellist.size();j++){
                if(labellist.at(j)==label){
                    images.push_back(cv::imread("/home/ubuntu/project4/dataset/"+filename, CV_LOAD_IMAGE_GRAYSCALE));
                    labels.push_back(j+3);
                }
            }
        }



        cv::Ptr<cv::FaceRecognizer> model = cv::createFisherFaceRecognizer();
        //訓練
        model->train(images, labels);
        cv::Mat img = cv::imread("/home/ubuntu/project4/test.jpg", CV_LOAD_IMAGE_GRAYSCALE);
        cv::resize(img, img, cv::Size(50, 50));
        //測試
        int predicted = model->predict(img);
        return predicted;
}


void MainWindow::on_Face_clicked()
{
    facedetect=myShowImage;
    facedetect = facedetect.scaled(200,150 ,Qt::KeepAspectRatio);
    facedetect.save("/home/ubuntu/project4/test.jpg");
    cv::Mat img2 = cv::imread("/home/ubuntu/project4/test.jpg", CV_LOAD_IMAGE_ANYCOLOR);
    VideoCapture *v=new VideoCapture();
    facedetect = convertProcess(v->facedetectdrow(img2,false,"0"));
    img2=peopleDetecte(QImage2cvMat(facedetect));
    facedetect = convertProcess(img2);
    ui->facetext->setText("Number of faces: "+QString::number(v->getfacesize()));
    ui->Detect->setPixmap(QPixmap::fromImage(facedetect).scaled(400,300,Qt::KeepAspectRatio));
//    cv::Mat ee;
//    ee=QImage2cvMat(facedetect);
    int predict;
    predict=trainModel();
    QString str = QString::number(numberofpeople);
    ui->peopletext->setText("number of people: "+str);
    if (predict==0){
       ui->nametext->setText("107598012");
    }
    else if (predict==1){
       ui->nametext->setText("107598002");
    }
    else if (predict==2){
        ui->nametext->setText("-1");
    }
    else if (predict>=3){
        ui->nametext->setText(labellist.at(predict-3));
    }
    if(v->getfacesize()==0)
    {
        ui->nametext->setText("-1");
    }
    std::cout<<predict;
    cv::waitKey(1000); //delay


}

void MainWindow::on_Addface_clicked()
{
   pi=true;
   Dialog D;
   D.add(ttttt);
   D.setModal(true);
   D.exec();

   VideoCapture *v=new VideoCapture();
   v->facedetectdrow(ttttt,true,D.name());
}

void MainWindow::removeListSame(QStringList *list)
{
    for (int i = 0; i < list->count(); i++)
    {
        for (int k = i + 1; k <  list->count(); k++)
        {
            if ( list->at(i) ==  list->at(k))
            {
                list->removeAt(k);
                k--;
            }
        }
    }
}


cv::Mat MainWindow::peopleDetecte(cv::Mat img){
    numberofpeople=0;
    std::vector <cv::Rect> found, found_filtered;
       cv::HOGDescriptor people_dectect_hog;
           // 採用默認的已經訓練好了的svm係數作為此次檢測的模型
       people_dectect_hog.setSVMDetector(cv::HOGDescriptor::getDefaultPeopleDetector());
            // 對輸入的圖片img進行多尺度行人檢測
            // img為輸入待檢測的圖片；found為檢測到目標區域列表；參數3為程序內部計算為行人目標的閾值，也就是檢測到的特徵到SVM分類超平面的距離;
            // 參數4為滑動窗口每次移動的距離。它必須是塊移動的整數倍；參數5為圖像擴充的大小；參數6為比例係數，即測試圖片每次尺寸縮放增加的比例；
            // 參數7為組閾值，即校正係數，當一個目標被多個窗口檢測出來時，該參數此時就起了調節作用，為0時表示不起調節作用。
       people_dectect_hog.detectMultiScale(img, found, 0 , cv::Size( 8 , 8 ), cv::Size( 32 , 32 ), 1.05 , 2 );

           size_t i, j;

           for (int i=0;i<found.size();i++)
           {
               cv::Rect r=found[i];
               // 下面的這個for語句是找出所有沒有嵌套的矩形框r,並放入found_filtered中,如果有嵌套的
               // 話,則取外面最大的那個矩形框放入found_filtered中
               for (j = 0 ; j <found.size(); j++ )
                    if (j != i && (r&found[j])== r)
                        break ;
                if (j == found.size())
                  found_filtered.push_back(r);
           }

           // 在圖片img上畫出矩形框,因為hog檢測出的矩形框比實際人體框要稍微大些,所以這裡需要
            // 做一些調整
            numberofpeople=found_filtered.size();
           for (i = 0 ; i <found_filtered.size(); i++ )
               {
                   cv::Rect r = found_filtered[i];
                   r.x += cvRound(r.width* 0.1 );
                   r.width = cvRound(r.width* 0.8 );
                   r.y += cvRound(r.height* 0.07 );
                   r.height = cvRound(r.height* 0.8 );
                   rectangle(img, r.tl(), r.br(), cv::Scalar( 0 , 255 , 0 ), 3 );
               }
           return img;

}

