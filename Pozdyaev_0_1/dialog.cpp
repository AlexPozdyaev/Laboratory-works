#include "dialog.h"
#include "ui_dialog.h"
#include "bignum.h"

Dialog::Dialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog)
{
    ui->setupUi(this);
    ui->lineEdit->setFocus();
    ui->lineEdit->setSelection(0,255);
}

Dialog::~Dialog()
{
    delete ui;
}

void Dialog::on_pushButton_clicked()
{
    BigNum a(ui->lineEdit->text());
    BigNum b(ui->lineEdit_2->text());
    BigNum c = a + b;
    ui->label_3->setText(c.toString());
}

void Dialog::on_pushButton_2_clicked()
{
     BigNum a(ui->lineEdit->text());
     BigNum b(ui->lineEdit_2->text());
     BigNum c = a - b;
     ui->label_3->setText(c.toString());
}


