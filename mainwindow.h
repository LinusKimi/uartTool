#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtDebug>

#include <QMainWindow>
#include <QFileDialog>
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

private:
    Ui::MainWindow *ui;

    // 和页面相关
    bool isConnected = false;
    bool isOpenjiliFile = false;
    bool isShowHexCode = false;

    // 和逻辑相关
    bool isShowData = true;

    void connectInterFunction();
};
#endif // MAINWINDOW_H
