#include <QThread>
#include <iostream>
#include "messageThread.h"
#include "QtDebug"
MessageThread::MessageThread(Controller *lightController )
{
    this->stopped = false;
    this->_lightController = lightController;
}

void MessageThread::setMessage(const int message){
    this->msg = message;
}

void MessageThread::stop(){
    this->stopped = true;
}

void MessageThread::run(){
    while(!stopped)
    {
        switch(msg)
        {
        case 10: //spark
            QThread::sleep(1);
            _lightController->openAllLights();
            QThread::sleep(1);
            _lightController->closeAllLights();
            break;
        case 9: //dark
            _lightController->closeAllLights();
            break;
        case 99:
            _lightController->unexportAllLight();
            break;
        case 0: // open first light 00
            _lightController->open(0);
            _lightController->close(1);
            _lightController->close(2);
            break;
        case 1: //01
            _lightController->open(0);
            _lightController->close(1);
            _lightController->open(2);
            break;
        case 2: //10
            _lightController->open(0);
            _lightController->open(1);
            _lightController->close(2);
            break;
        case 3: //11
            _lightController->open(0);
            _lightController->open(1);
            _lightController->open(2);
            break;
        }

    }

}

