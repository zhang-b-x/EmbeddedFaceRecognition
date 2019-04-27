#ifndef CAMERACMS_H
#define CAMERACMS_H

#include <QDialog>
#include <QLabel>


namespace Ui {
class Cameracms;
}

class Cameracms : public QDialog
{
    Q_OBJECT

public:
    explicit Cameracms(QWidget *parent = 0);
    ~Cameracms();

private slots:
    void on_pushButton_clicked();

private slots:
    void receivemainwin();

    void on_pushButton_2_clicked();

signals:
    void ltdialog();

private:
    Ui::Cameracms *ui;

private:
    //Ui::Cameracms *ui;
    QLabel *label ;
};

#endif // CAMERACMS_H

