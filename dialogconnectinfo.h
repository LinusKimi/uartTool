#ifndef DIALOGCONNECTINFO_H
#define DIALOGCONNECTINFO_H

#include <QtDebug>
#include <QDialog>
#include <QMouseEvent>

#include <QtSerialPort/QSerialPort>
#include <QtSerialPort/QSerialPortInfo>

#include <data/serialreadwrite.h>

namespace Ui {
class DialogConnectInfo;
}

typedef struct
{
    // 是否 串口 default : true
    bool isSerial;

    SerialSettings serialSetting;

    // 网络
    // ... 待定

}FrameData;

class DialogConnectInfo : public QDialog
{
    Q_OBJECT

public:
    explicit DialogConnectInfo(QWidget *parent = nullptr);
    ~DialogConnectInfo();

    // 页面整合 数据类型
    FrameData _frameData;

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

    void addSerialItems();

    void initUiItems();

private:
    Ui::DialogConnectInfo *ui;

signals:
    void sendData(FrameData);
};

#endif // DIALOGCONNECTINFO_H
