#ifndef ABSTRACTREADWRITE_H
#define ABSTRACTREADWRITE_H

#include <QtCore/QObject>

class AbsTractReadWrite: public QObject
{
    Q_OBJECT
public:
    explicit AbsTractReadWrite(QObject *parent = nullptr);

    virtual QString getSettingText() const = 0;

    virtual bool open() = 0;

    virtual void cloese() = 0;

    virtual bool isOpen() = 0;

    virtual bool isConnected() = 0;

    virtual QByteArray readAll() = 0;

    virtual qint64 write(const QByteArray &) const = 0;

signals:

    void readyRead();
};

#endif // ABSTRACTREADWRITE_H
