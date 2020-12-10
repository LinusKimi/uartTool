#ifndef DIALOGCONNECTINFO_H
#define DIALOGCONNECTINFO_H

#include <QtDebug>
#include <QDialog>
#include <QMouseEvent>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

namespace Ui {
class DialogConnectInfo;
}

class DialogConnectInfo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConnectInfo(QWidget *parent = nullptr);
    ~DialogConnectInfo();

    // 页面整合 数据类型
    typedef struct
    {
        // 是否 串口 default : true
        bool isSerial;
        QString serialPort[5];

        // 网络
        // ... 待定

    }FrameData;

    FrameData _frameData = {true, {0}};

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void addSerialItems();

private:
    Ui::DialogConnectInfo *ui;

signals:
    void sendData(FrameData);
};

#endif // DIALOGCONNECTINFO_H
