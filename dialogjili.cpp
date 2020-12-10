#include "dialogjili.h"
#include "ui_dialogjili.h"

DialogJili::DialogJili(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogJili)
{
    ui->setupUi(this);

    ui->lineEdit->setEnabled(false);
}

DialogJili::~DialogJili()
{
    delete ui;
}

void DialogJili::on_radioButton_clicked()
{
    this->infiniteStyle = true;
    ui->lineEdit->setEnabled(false);
}

void DialogJili::on_radioButton_2_clicked()
{
    this->infiniteStyle = false;
    ui->lineEdit->setEnabled(true);
}

void DialogJili::on_buttonBox_rejected()
{
    this->close();
}

void DialogJili::on_buttonBox_accepted()
{
    emit sendData(infiniteStyle, (int64_t)ui->lineEdit->text().toLong());
}
