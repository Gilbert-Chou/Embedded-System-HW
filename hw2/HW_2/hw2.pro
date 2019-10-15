#-------------------------------------------------
#
# Project created by QtCreator 2019-10-13T15:07:57
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = hw2
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h \
    image_process.h \
    gray.h \
    eq_hist.h \
    blur.h \
    mean_blur.h \
    median_blur.h \
    gaussian_blur.h \
    bilateral_blur.h \
    threshold.h \
    dilate.h \
    erode.h \
    morph_open.h \
    morph_close.h \
    morph_gradient.h \
    morph_tophat.h \
    morph_blackhat.h

FORMS    += mainwindow.ui

INCLUDEPATH += /usr/include

LIBS +=/usr/local/lib/libopencv_imgproc.so \
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
