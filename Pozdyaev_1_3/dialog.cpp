#include "dialog.h"
#include "ui_dialog.h"
#include "bignum.h"

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
 // слот для кнопки < * >:
void Dialog::on_pushButton_clicked()
{
    BigNum a(ui->lineEdit->text()); // используем основной конструктор
    BigNum b(ui->lineEdit_2->text());
    BigNum c = a * b;
    ui->label_3->setText(c.toString()); // выводим результат
}


