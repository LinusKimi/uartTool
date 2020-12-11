#ifndef SERIALCONTROLLER_H
#define SERIALCONTROLLER_H

#include <QObject>

class SerialController: public QObject
{
    Q_OBJECT
public:
    SerialController();

//    SerialController(SerialController *serialController);

//    ~SerialController() override;

    void setData(QString);

    void setIsHex(bool);

//    virtual QByteArray getNextFrame() = 0;

//    virtual qint64 getTotalCount() = 0;

};

#endif // SERIALCONTROLLER_H
