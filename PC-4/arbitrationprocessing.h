#ifndef ARBITRATIONPROCESSING_H
#define ARBITRATIONPROCESSING_H

#include <QDialog>
#include "qlabel.h"

namespace Ui {
class ArbitrationProcessing;
}

class ArbitrationProcessing : public QDialog
{
    Q_OBJECT

public:
    explicit ArbitrationProcessing(QWidget *parent = 0);
    ~ArbitrationProcessing();

private:
    Ui::ArbitrationProcessing *ui;

private slots:
    void receiveDialogA();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();


private:
    QLabel *label ;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;

signals:
    void showDialogAr();
};


#endif // ARBITRATIONPROCESSING_H
