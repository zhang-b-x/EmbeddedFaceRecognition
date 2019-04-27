#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel>

namespace Ui {
class Dialog;
}

class Dialog : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog(QWidget *parent = 0);
    ~Dialog();

private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private slots:          //用于接受来自相机界面的信号
    void receivecam();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

signals:                //信号，显示主界面
    void showmainw();

private:
    Ui::Dialog *ui;
    QLabel *label;
    QLabel *label2;
};

#endif // DIALOG_H

