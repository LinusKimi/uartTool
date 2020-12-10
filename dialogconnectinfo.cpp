#include "dialogconnectinfo.h"
#include "ui_dialogconnectinfo.h"

DialogConnectInfo::DialogConnectInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConnectInfo)
{
    ui->setupUi(this);

    addSerialItems();
}

DialogConnectInfo::~DialogConnectInfo()
{
    delete ui;
}

void DialogConnectInfo::on_buttonBox_accepted()
{
    emit sendData(_frameData);
    this->close();
}

void DialogConnectInfo::on_buttonBox_rejected()
{
    this->close();
}

void DialogConnectInfo::addSerialItems()
{
    QList<QSerialPortInfo> serialList;
    QList<QString> serialNameList;
    serialList = QSerialPortInfo::availablePorts();

    ui->comboBox->clear();
    foreach(QSerialPortInfo i, serialList){
        serialNameList.append(i.portName());
    }

    // sort low than
    qSort(serialNameList.begin(), serialNameList.end());

    foreach(QString i, serialNameList)
    {
        ui->comboBox->addItem(i);
    }
}
