#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QThread"
#include <string>
#include <pthread.h>
#include <QDebug>
#include <vector>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->Slider->setValue(0);
    ui->Slider->setMaximum(3);
    ui->Slider->setMinimum(0);
    ui->lineEdit->setText("0");
    std::vector<Gpio*> lights;
    lights.push_back(new Gpio(164));
    lights.push_back(new Gpio(165));
    lights.push_back(new Gpio(166));
    Controller* c = new Controller(lights);
    thread = new MessageThread(c);
    thread->start();
    thread->setMessage(10);
    _state = INIT;
}

MainWindow::~MainWindow()
{
    thread->setMessage(99);
    delete ui;
}

void MainWindow::controllAllLight(string isOpen)
{
    if(isOpen == "close")
    {
        _gpio_164->gpio_set_value(0);
        _gpio_165->gpio_set_value(0);
        _gpio_166->gpio_set_value(0);
    }
    else if (isOpen == "open")
    {
        _gpio_164->gpio_set_value(1);
        _gpio_165->gpio_set_value(1);
        _gpio_166->gpio_set_value(1);
    }
}

void MainWindow::on_startButton_clicked()
{

    _state = START;
    ui->startButton->setEnabled(false);
    ui->stopButton->setEnabled(true);
    ui->resetButton->setEnabled(true);
    ui->lineEdit->setText("0");
    ui->Slider->setValue(0);
    thread->setMessage(0);
}

void MainWindow::on_stopButton_clicked()
{
    _state = STOP;
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
    ui->resetButton->setEnabled(true);
    thread->setMessage(9);
}

void MainWindow::on_resetButton_clicked()
{
    _state = INIT;
    ui->startButton->setEnabled(true);
    ui->stopButton->setEnabled(false);
    ui->resetButton->setEnabled(false);
    thread->setMessage(10);
    ui->lineEdit->setText("0");
    ui->Slider->setValue(0);
}

void MainWindow::on_Slider_valueChanged(int value)
{
    ui->lineEdit->setText(QString::number(value));
    if(_state == START)
    {
        thread->setMessage(value);
    }
}

void MainWindow::on_lineEdit_textEdited(const QString &arg1)
{

    ui->Slider->setValue(arg1.toInt());
}

void MainWindow::on_lineEdit_textChanged(const QString &arg1)
{
    if (arg1.toInt()>3 )
    {
        ui->lineEdit->setText("3");
    }
    else if(arg1.toInt()< 0)
    {
        ui->lineEdit->setText("0");
    }
    else{
        ui->lineEdit->setText(arg1);
    }
}
