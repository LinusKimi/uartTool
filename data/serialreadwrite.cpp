#include "serialreadwrite.h"

SerialReadWrite::SerialReadWrite(QObject *parent): AbsTractReadWrite(parent)
{

}

QString SerialReadWrite::getSettingText() const
{
    return QString("%1 %2 %3 %4 %5").arg(settings.name).arg(settings.baudRate).arg(settings.dataBits).arg(settings.stopBits).arg(settings.parity);
}

bool SerialReadWrite::open()
{
    cloese();

    serial = new QSerialPort(this);
    serial->setPortName(settings.name);
    serial->setBaudRate(settings.baudRate);
    serial->setDataBits(settings.dataBits);
    serial->setParity(settings.parity);
    serial->setStopBits(settings.stopBits);
//    serial->setFlowControl(settings.flowControl);

    if(serial->open(QIODevice::ReadWrite))
    {
        connect(serial, &QSerialPort::readyRead,this, &SerialReadWrite::readyRead);
        return true;
    }
    else
    {
        serial = nullptr;
        return false;
    }
}

void SerialReadWrite::cloese()
{
    if(serial != nullptr)
    {
        serial->close();
        delete serial;
        serial = nullptr;
    }
}

bool SerialReadWrite::isOpen()
{
    return serial != nullptr && serial->isOpen();
}

bool SerialReadWrite::isConnected()
{
    return serial != nullptr && serial->isOpen();
}

QByteArray SerialReadWrite::readAll()
{
    if(serial != nullptr && serial->isOpen())
        return serial->readAll();

    qDebug() << "SerialReadWriter readAll() _serial == nullptr or not open";

    return QByteArray();
}


qint64 SerialReadWrite::write(const QByteArray &byteArray) const
{
    if (serial != nullptr && serial->isOpen())
        return serial->write(byteArray);

    qDebug() << "SerialReadWriter readAll() _serial == nullptr or not open";

    return 0;
}

void SerialReadWrite::setSerialSetting(SerialSettings serialSettings)
{
    this->settings = std::move(serialSettings);
}
