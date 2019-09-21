#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <string>
#include "messageThread.h"
class Gpio;
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
    void on_startButton_clicked();

    void on_stopButton_clicked();

    void on_resetButton_clicked();

    void on_Slider_valueChanged(int value);

    void on_lineEdit_textEdited(const QString &arg1);

    void controllAllLight(std::string isOpen);

    void on_lineEdit_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    Gpio* _gpio_164 ;
    Gpio* _gpio_165 ;
    Gpio* _gpio_166 ;
    MessageThread* thread;
    enum _status{INIT, START ,STOP };
    _status _state;
};

#endif // MAINWINDOW_H
