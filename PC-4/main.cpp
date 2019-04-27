#include "mainwindow.h"
#include "dialog.h"
#include "singleprocessing.h"
#include "batchprocessing.h"
#include "arbitrationprocessing.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    Dialog w1;
    singleProcessing w2;
    batchProcessing w3;
    ArbitrationProcessing w4;

    w.show();

    QObject::connect(&w,SIGNAL(showDialog()),&w1,SLOT(receiveMain()));
    QObject::connect(&w1,SIGNAL(showSingle()),&w2,SLOT(receiveDialog()));
    QObject::connect(&w1,SIGNAL(showBatch()),&w3,SLOT(receiveDialog2()));
    QObject::connect(&w2,SIGNAL(showDialog2()),&w1,SLOT(receiveSingle()));
    QObject::connect(&w3,SIGNAL(showDialogB()),&w1,SLOT(receiveBatch()));
    QObject::connect(&w1,SIGNAL(showArbit()),&w4,SLOT(receiveDialogA()));
    QObject::connect(&w4,SIGNAL(showDialogAr()),&w1,SLOT(receiveArbit()));
    return a.exec();
}


