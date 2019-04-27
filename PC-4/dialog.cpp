#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::receiveMain()
{
    this->show();
}

void Dialog::receiveSingle()
{
    this->show();
}

void Dialog::receiveBatch()
{
    this->show();
}

void Dialog::receiveArbit()
{
    this->show();
}

void Dialog::on_pushButton_clicked()
{
    this->hide();
    emit showSingle();
}

void Dialog::on_pushButton_2_clicked()
{
    this->hide();
    emit showBatch();
}

void Dialog::on_pushButton_3_clicked()
{
    this->hide();
    emit showArbit();
}


