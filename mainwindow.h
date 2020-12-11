#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtDebug>

#include <QMainWindow>
#include <QFileDialog>
#include <QLabel>
#include <QLineEdit>
#include <QStandardItemModel>
#include <QItemSelectionModel>
#include <QTimer>

#include <dialogconnectinfo.h>
#include <dialogjili.h>
#include <globalfunction.h>
#include <incentivedoc.h>

#include "data/abstractreadwrite.h"
#include "data/serialreadwrite.h"

#include "serial/serialcontroller.h"


QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void MesStatusBar();

private:
    Ui::MainWindow *ui;

    // status bar collecter
    uint64_t sendCnt = 0;
    uint64_t recvCnt = 0;
    QLabel *statusBarReadBytesLabel, *statusBarWriteBytesLabel;

    // 和页面相关
    bool isConnected = false;
    bool isOpenjiliFile = false;
    bool isShowHexCode = false;

    // 和逻辑相关
    bool isShowData = true;

    //
    FrameData _frameData;
    JILIType  _jiliType;

    AbsTractReadWrite *_readWrite{nullptr};


    // 初始化 tabview
    void initTabView();

    // 连接内部槽函数
    void connectInterFunction();

    void statusBarRecvBytesCnt();
    void statusBarSendBytesCnt();

    void displayReceiveData(const QByteArray &);
    void displaySendData(const QByteArray &);

};
#endif // MAINWINDOW_H
