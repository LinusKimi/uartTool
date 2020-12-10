#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MesStatusBar();
    connectInterFunction();

    ui->statusbar->showMessage("就绪");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::MesStatusBar()
{
    statusBar()->setSizeGripEnabled(false);//去掉状态栏右下角的三角

    auto receiveByteCountLabel = new QLabel(tr("接收 "), this);
    statusBarReadBytesLabel = new QLabel(this);
    statusBarReadBytesLabel->setMinimumWidth(100);
    statusBarReadBytesLabel->setText(QString::number(recvCnt));

    auto sendByteCountLabel = new QLabel(tr("发送 "), this);
    statusBarWriteBytesLabel = new QLabel(this);
    statusBarWriteBytesLabel->setMinimumWidth(100);
    statusBarWriteBytesLabel->setText(QString::number(sendCnt));

    statusBar()->addPermanentWidget(receiveByteCountLabel);
    statusBar()->addPermanentWidget(statusBarReadBytesLabel);
    statusBar()->addPermanentWidget(sendByteCountLabel);
    statusBar()->addPermanentWidget(statusBarWriteBytesLabel);
}

void MainWindow::connectInterFunction()
{
    // 新建 激励文件
    connect(ui->actionCreateFile, &QAction::triggered, [](){
        QString _fileName = QFileDialog::getSaveFileName(NULL, "新建激励文件", "./", "文本文件(*cl)");
        _fileName += ".cl";

        if(_fileName.isNull());
        else
        {
            qDebug() << _fileName;


        }
    });

    // 打开 激励文件
    connect(ui->actionOpenFile, &QAction::triggered,[](){
        qDebug() << "打开 激励文件";
        QString _fileName = QFileDialog::getOpenFileName(NULL, "新建激励文件", "./", "文本文件(*cl)");

        if(_fileName.isNull());
        else
        {
            qDebug() << _fileName;

        }
    });

    // 启动连接
    connect(ui->actionConnect, &QAction::triggered,[&](){
        qDebug() << "action Connected!";

        if(isConnected == false)
        {

            isConnected = true;
            ui->actionConnect->setIcon(QIcon(":/images/resource/img/connectStop.png"));
            ui->actionConnect->setText("关闭");
        }
        else
        {

            isConnected = false;
            ui->actionConnect->setIcon(QIcon(":/images/resource/img/connectStart.png"));
            ui->actionConnect->setText("打开");
        }

    });

    // 连接方式
    connect(ui->actionConnectInfo, &QAction::triggered,[&](){
        ui->actionConnectInfo->setChecked(false);
        DialogConnectInfo *_connectInfo = new DialogConnectInfo();
        _connectInfo->setWindowModality(Qt::ApplicationModal);
        _connectInfo->show();

        connect(_connectInfo, &DialogConnectInfo::sendData,[&](DialogConnectInfo::FrameData _frameData){
            qDebug() << _frameData.isSerial;
        });
    });

    // hex 显示
    connect(ui->actionHEX, &QAction::triggered,[&](){

    });

    // 清除显示
    connect(ui->actionClearData, &QAction::triggered,[&](){

    });
    // 是否显示
    connect(ui->actionDataShow, &QAction::triggered,[&](){
        if(isShowData == false)
        {
            isShowData = true;
            ui->actionDataShow->setIcon(QIcon(":/images/resource/img/enableShow.png"));
            ui->actionDataShow->setText("显示");

            ui->tableView->show();
        }
        else
        {
            ui->actionDataShow->setIcon(QIcon(":/images/resource/img/disableShow.png"));
            ui->actionDataShow->setText("屏蔽");
            isShowData = false;

            ui->tableView->hide();
        }
    });

    // 触发激励
    connect(ui->actionJiLi, &QAction::triggered,[&](){
        ui->actionJiLi->setChecked(false);
        DialogJili *_jili = new DialogJili();
        _jili->setWindowModality(Qt::ApplicationModal);
        _jili->show();

        connect(_jili, &DialogJili::sendData, [&](bool i, int64_t j){
           qDebug() << i << j;
        });
    });

    // 停止激励
    connect(ui->actionJiLiStop, &QAction::triggered,[&](){

    });

    // 添加激励
    connect(ui->actionAddJiLi, &QAction::triggered,[&](){

    });
}
