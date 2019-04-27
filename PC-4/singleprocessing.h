#ifndef SINGLEPROCESSING_H
#define SINGLEPROCESSING_H

#include <QDialog>
#include <QLabel>
namespace Ui {
class singleProcessing;
}

class singleProcessing : public QDialog
{
    Q_OBJECT

public:
    explicit singleProcessing(QWidget *parent = 0);
    ~singleProcessing();

private:
    Ui::singleProcessing *ui;

private:
    QLabel *label ;
    QLabel *label2;
    QLabel *label3;
private slots:
    void receiveDialog();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_3_clicked();

    void on_pushButton_5_clicked();

signals:
    void showDialog2();
};

#endif // SINGLEPROCESSING_H


