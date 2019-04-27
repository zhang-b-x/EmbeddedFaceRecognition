#-------------------------------------------------
#
# Project created by QtCreator 2018-06-02T01:49:06
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = PC-4
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

INCLUDEPATH+=/usr/include/opencv
LIBS+=/usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4
LIBS+=/usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4
LIBS+=/usr/lib/x86_64-linux-gnu/libopencv_core.so.2.4
LIBS+=/usr/lib/x86_64-linux-gnu/libopencv_highgui.so.2.4
LIBS+=/usr/lib/x86_64-linux-gnu/libopencv_calib3d.so.2.4
LIBS+=/usr/lib/x86_64-linux-gnu/libopencv_contrib.so.2.4
LIBS+=/usr/lib/x86_64-linux-gnu/libopencv_features2d.so.2.4
LIBS+=/usr/lib/x86_64-linux-gnu/libopencv_flann.so.2.4
LIBS+=/usr/lib/x86_64-linux-gnu/libopencv_gpu.so.2.4
LIBS+=/usr/lib/x86_64-linux-gnu/libopencv_imgproc.so.2.4
LIBS+=/usr/lib/x86_64-linux-gnu/libopencv_legacy.so.2.4
LIBS+=/usr/lib/x86_64-linux-gnu/libopencv_ml.so.2.4
LIBS+=/usr/lib/x86_64-linux-gnu/libopencv_objdetect.so.2.4
LIBS+=/usr/lib/x86_64-linux-gnu/libopencv_video.so.2.4

SOURCES += \
        main.cpp \
        mainwindow.cpp \
    dialog.cpp \
    singleprocessing.cpp \
    batchprocessing.cpp \
    arbitrationprocessing.cpp

HEADERS += \
        mainwindow.h \
    dialog.h \
    singleprocessing.h \
    batchprocessing.h \
    arbitrationprocessing.h

FORMS += \
        mainwindow.ui \
    dialog.ui \
    singleprocessing.ui \
    batchprocessing.ui \
    arbitrationprocessing.ui

RESOURCES += \
    logo.qrc
