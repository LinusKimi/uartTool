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
    _jiliType.infiniteStyle = true;
    ui->lineEdit->setEnabled(false);
}

void DialogJili::on_radioButton_2_clicked()
{
    _jiliType.infiniteStyle = false;
    ui->lineEdit->setEnabled(true);
}

void DialogJili::on_buttonBox_rejected()
{
    this->close();
}

void DialogJili::on_buttonBox_accepted()
{
    _jiliType.finitudeCnt = (int64_t)ui->lineEdit->text().toLong();
    emit sendData(_jiliType);
}
