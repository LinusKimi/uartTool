#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtDebug>

#include <QMainWindow>
#include <QFileDialog>
#include <QLabel>

#include <dialogconnectinfo.h>
#include <dialogjili.h>



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
    qint64 sendCnt = 0;
    qint64 recvCnt = 0;
    QLabel *statusBarReadBytesLabel, *statusBarWriteBytesLabel;

    // 和页面相关
    bool isConnected = false;
    bool isOpenjiliFile = false;
    bool isShowHexCode = false;

    // 和逻辑相关
    bool isShowData = true;

    void connectInterFunction();
};
#endif // MAINWINDOW_H
