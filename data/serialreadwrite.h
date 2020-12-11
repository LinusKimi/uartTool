#ifndef SERIALREADWRITE_H
#define SERIALREADWRITE_H

#include <QtDebug>

#include <QObject>
#include <QSerialPort>
#include "data/abstractreadwrite.h"

struct SerialSettings{
    QString name;
    qint32 baudRate;
    QSerialPort::DataBits dataBits;
    QSerialPort::Parity parity;
    QSerialPort::StopBits stopBits;
//    QSerialPort::FlowControl flowControl;
//    bool localEchoEnabled;
};

class SerialReadWrite: public AbsTractReadWrite
{
    Q_OBJECT
public:
    explicit SerialReadWrite(QObject *parent = nullptr);

    QString getSettingText() const override;

    bool open() override;

    void cloese() override;

    bool isOpen() override;

    bool isConnected() override;

    QByteArray readAll() override;

    qint64 write(const QByteArray &) const override;

    void setSerialSetting(SerialSettings);

private:
    SerialSettings settings;
    QSerialPort *serial{nullptr};

};

#endif // SERIALREADWRITE_H
