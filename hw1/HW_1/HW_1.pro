#-------------------------------------------------
#
# Project created by QtCreator 2019-09-20T16:53:52
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = HW_1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    gpio.cpp \
    messageThread.cpp \
    lightController.cpp

HEADERS  += mainwindow.h \
    messageThread.h

FORMS    += mainwindow.ui
