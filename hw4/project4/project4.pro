#-------------------------------------------------
#
# Project created by QtCreator 2019-11-26T16:25:03
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = project4
TEMPLATE = app


LIBS += /usr/local/lib/libopencv_nonfree.so \
/usr/local/lib/libopencv_imgproc.so \
/usr/local/lib/libopencv_highgui.so \
/usr/local/lib/libopencv_core.so \
/usr/local/lib/libopencv_calib3d.so \
/usr/local/lib/libopencv_ml.so \
/usr/local/lib/libopencv_contrib.so \
/usr/local/lib/libopencv_photo.so \
/usr/local/lib/libopencv_legacy.so \
/usr/local/lib/libopencv_stitching.so \
/usr/local/lib/libopencv_features2d.so \
/usr/local/lib/libopencv_flann.so \
/usr/local/lib/libopencv_objdetect.so \
/usr/local/lib/libopencv_gpu.so \
/usr/local/lib/libopencv_video.so \
/usr/local/lib/libopencv_videostab.so \
/usr/local/lib/libopencv_superres.so

SOURCES += main.cpp\
        mainwindow.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    VideoCapture.h \
    Thread.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui
