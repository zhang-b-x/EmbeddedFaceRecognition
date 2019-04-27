#ifndef BATCHPROCESSING_H
#define BATCHPROCESSING_H

#include <QDialog>
#include "qlabel.h"
namespace Ui {
class batchProcessing;
}

class batchProcessing : public QDialog
{
    Q_OBJECT

public:
    explicit batchProcessing(QWidget *parent = 0);
    ~batchProcessing();

private:
    Ui::batchProcessing *ui;

private slots:
    void receiveDialog2();
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

signals:
    void showDialogB();

private:
    QLabel *label ;
    QLabel *label2;
    QLabel *label3;
    QLabel *label4;
};

#endif // BATCHPROCESSING_H

