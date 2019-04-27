#-------------------------------------------------
#
# Project created by QtCreator 2018-05-04T16:51:59
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled4
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
        mainwindow.cpp \
    dialog.cpp \
    cameracms.cpp


INCLUDEPATH += /usr/local/opencv/opencv-2.4.13/arm/include
LIBS += /usr/local/opencv/opencv-2.4.13/arm/lib/libopencv_calib3d.so
LIBS += /usr/local/opencv/opencv-2.4.13/arm/lib/libopencv_contrib.so
LIBS += /usr/local/opencv/opencv-2.4.13/arm/lib/libopencv_core.so
LIBS += /usr/local/opencv/opencv-2.4.13/arm/lib/libopencv_features2d.so
LIBS += /usr/local/opencv/opencv-2.4.13/arm/lib/libopencv_flann.so
LIBS += /usr/local/opencv/opencv-2.4.13/arm/lib/libopencv_gpu.so
LIBS += /usr/local/opencv/opencv-2.4.13/arm/lib/libopencv_highgui.so
LIBS += /usr/local/opencv/opencv-2.4.13/arm/lib/libopencv_imgproc.so
LIBS += /usr/local/opencv/opencv-2.4.13/arm/lib/libopencv_legacy.so
LIBS += /usr/local/opencv/opencv-2.4.13/arm/lib/libopencv_ml.so
LIBS += /usr/local/opencv/opencv-2.4.13/arm/lib/libopencv_nonfree.so
LIBS += /usr/local/opencv/opencv-2.4.13/arm/lib/libopencv_objdetect.so
LIBS += /usr/local/opencv/opencv-2.4.13/arm/lib/libopencv_photo.so
LIBS += /usr/local/opencv/opencv-2.4.13/arm/lib/libopencv_stitching.so
LIBS += /usr/local/opencv/opencv-2.4.13/arm/lib/libopencv_superres.so
LIBS += /usr/local/opencv/opencv-2.4.13/arm/lib/libopencv_video.so
LIBS += /usr/local/opencv/opencv-2.4.13/arm/lib/libopencv_videostab.so


HEADERS += \
        mainwindow.h \
    dialog.h \
    cameracms.h

FORMS += \
        mainwindow.ui \
    dialog.ui \
    cameracms.ui

RESOURCES += \
    logoimage.qrc


