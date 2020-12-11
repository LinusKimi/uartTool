#include "dialogconnectinfo.h"
#include "ui_dialogconnectinfo.h"

DialogConnectInfo::DialogConnectInfo(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialogConnectInfo)
{
    ui->setupUi(this);

    initUiItems();

    addSerialItems();
}

DialogConnectInfo::~DialogConnectInfo()
{
    delete ui;
}

void DialogConnectInfo::on_buttonBox_accepted()
{
    _frameData.isSerial = ui->radioButton->isChecked();
    _frameData.serialSetting.name = ui->serialPortNameComboBox->currentText();
    _frameData.serialSetting.baudRate = ui->serialPortBaudRateComboBox->currentText().toInt();
    _frameData.serialSetting.dataBits = (QSerialPort::DataBits)ui->serialPortDataBitsComboBox->currentText().toInt();
    _frameData.serialSetting.parity = (QSerialPort::Parity)ui->serialPortParityComboBox->currentData().toInt();
    _frameData.serialSetting.stopBits = (QSerialPort::StopBits)ui->serialPortStopBitsComboBox->currentData().toInt();

    emit sendData(_frameData);
    this->close();
}

void DialogConnectInfo::on_buttonBox_rejected()
{
    this->close();
}

void DialogConnectInfo::initUiItems()
{
    ui->serialPortBaudRateComboBox->addItems(QStringList()
                                             << "1200"
                                             << "2400"
                                             << "4800"
                                             << "9600"
                                             << "19200"
                                             << "38400"
                                             << "25600"
                                             << "57600"
                                             << "115200"
                                             << "256000"
                                             );
    ui->serialPortDataBitsComboBox->addItems(QStringList() << "5" << "6" << "7" << "8");

    ui->serialPortStopBitsComboBox->addItem(tr("1"), QSerialPort::OneStop);
    ui->serialPortStopBitsComboBox->addItem(tr("1.5"), QSerialPort::OneAndHalfStop);
    ui->serialPortStopBitsComboBox->addItem(tr("2"), QSerialPort::TwoStop);

    ui->serialPortParityComboBox->addItem(tr("无校验"), QSerialPort::NoParity);
    ui->serialPortParityComboBox->addItem(tr("奇校验"), QSerialPort::OddParity);
    ui->serialPortParityComboBox->addItem(tr("偶校验"), QSerialPort::EvenParity);
    ui->serialPortParityComboBox->addItem(tr("空校验"), QSerialPort::SpaceParity);
    ui->serialPortParityComboBox->addItem(tr("标志校验"), QSerialPort::MarkParity);

    ui->serialPortDataBitsComboBox->setCurrentIndex(3);
    ui->serialPortBaudRateComboBox->setCurrentIndex(3);
}

void DialogConnectInfo::addSerialItems()
{
    QList<QSerialPortInfo> serialList;
    QList<QString> serialNameList;
    serialList = QSerialPortInfo::availablePorts();

    ui->serialPortNameComboBox->clear();
    foreach(QSerialPortInfo i, serialList){
        serialNameList.append(i.portName());
    }

    // sort low than
    qSort(serialNameList.begin(), serialNameList.end());

    foreach(QString i, serialNameList)
    {
        ui->serialPortNameComboBox->addItem(i);
    }
}
