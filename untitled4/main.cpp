#include <iostream>
#include <QApplication>


#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/objdetect/objdetect.hpp>

#include "mainwindow.h"
#include "dialog.h"
#include "cameracms.h"
using namespace cv;
using namespace std;
int main(int argc, char *argv[])
{

    QApplication a(argc, argv);
    MainWindow w;
    Dialog w1;

    Cameracms w2;
    w.show();
    QObject::connect(&w,SIGNAL(cameradialog()),&w2,SLOT(receivemainwin()) );
    QObject::connect(&w2,SIGNAL(ltdialog()),&w1,SLOT(receivecam()));
    QObject::connect(&w1,SIGNAL(showmainw()),&w2,SLOT(receivemainwin()));

    //w1.show();
    //w2.show();
    return a.exec();
    //CascadeClassifier
}


