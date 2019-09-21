#ifndef MESSAGETHREAD_H
#define MESSAGETHREAD_H
#include <QThread>
#include <iostream>
#include "lightController.cpp"

class MessageThread :public QThread
{
    Q_OBJECT

public:
    MessageThread(Controller *lightController );
    void setMessage(const int message);
    void stop();

protected:
    void run();

private:
    int msg;
    bool stopped;
    Controller* _lightController;
};

#endif // MESSAGETHREAD_H
