#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    MesStatusBar();
    connectInterFunction();

    ui->actionJiLi->setEnabled(false);
    ui->actionJiLiStop->setEnabled(false);
    ui->statusbar->showMessage("就绪");

    initTabView();

//    ui->tableView->hide();
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

void MainWindow::initTabView()
{


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
            if(_readWrite != nullptr)
            {
                _readWrite->cloese();
                delete _readWrite;
                _readWrite = nullptr;
            }

            bool i_result = false;

            // 是否 串口
            if(_frameData.isSerial)
            {
                auto readwriter = new SerialReadWrite();
                readwriter->setSerialSetting(_frameData.serialSetting);
                i_result = readwriter->open();

                if(!i_result)
                {
                    ui->statusbar->showMessage("串口被占用或者不存在!");
                    return ;
                }
                _readWrite = readwriter;
                ui->actionConnectInfo->setEnabled(false);
                ui->statusbar->showMessage(QString("%1 %2 %3 %4 %5 打开").arg(_frameData.serialSetting.name)
                                           .arg(_frameData.serialSetting.baudRate).arg(_frameData.serialSetting.dataBits)
                                           .arg(_frameData.serialSetting.parity).arg(_frameData.serialSetting.stopBits));
            }
            else
            {
                ;
            }

            connect(_readWrite, &AbsTractReadWrite::readyRead, [&](){
                auto data = _readWrite->readAll();
                if(!data.isEmpty())
                {
                    displayReceiveData(data);
                    recvCnt += data.count();
                    statusBarRecvBytesCnt();
                }
            });

            isConnected = true;
            ui->actionConnect->setIcon(QIcon(":/images/resource/img/connectStop.png"));
            ui->actionConnect->setText("关闭");
        }
        else
        {

            if(_readWrite != nullptr)
            {
                _readWrite->cloese();
                delete _readWrite;
                _readWrite = nullptr;
            }

            ui->actionConnectInfo->setEnabled(true);

            if(_frameData.isSerial)
                ui->statusbar->showMessage(QString("%1 %2 %3 %4 %5 关闭").arg(_frameData.serialSetting.name)
                                           .arg(_frameData.serialSetting.baudRate).arg(_frameData.serialSetting.dataBits)
                                           .arg(_frameData.serialSetting.parity).arg(_frameData.serialSetting.stopBits));
            else
                ui->statusbar->showMessage("ETH 关闭");

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

        connect(_connectInfo, &DialogConnectInfo::sendData,[&](FrameData _frameData){
            this->_frameData = std::move(_frameData);
            qDebug() << this->_frameData.isSerial;
        });
    });

    // hex 显示
    connect(ui->actionHEX, &QAction::triggered,[&](){
        if(isShowHexCode)
        {
            isShowHexCode = false;

        }
        else
        {
            isShowHexCode = true;
        }
    });

    // 清除显示
    connect(ui->actionClearData, &QAction::triggered,[&](){
        ui->textBrowser->clear();
        sendCnt = 0; recvCnt = 0;

        statusBarRecvBytesCnt();
    });
    // 是否显示
    connect(ui->actionDataShow, &QAction::triggered,[&](){
        if(isShowData == false)
        {
            isShowData = true;
            ui->actionDataShow->setIcon(QIcon(":/images/resource/img/enableShow.png"));
            ui->actionDataShow->setText("显示");

            ui->textBrowser->clear();
            ui->textBrowser->setEnabled(true);
        }
        else
        {
            ui->actionDataShow->setIcon(QIcon(":/images/resource/img/disableShow.png"));
            ui->actionDataShow->setText("屏蔽");
            isShowData = false;

            ui->textBrowser->setEnabled(false);
            ui->textBrowser->clear();

        }
    });

    // 触发激励
    connect(ui->actionJiLi, &QAction::triggered,[&](){
        ui->actionJiLi->setChecked(false);
        DialogJili *_jili = new DialogJili();
        _jili->setWindowModality(Qt::ApplicationModal);
        _jili->show();

        connect(_jili, &DialogJili::sendData, [&](JILIType _jili){
           qDebug() << _jili.infiniteStyle << _jili.finitudeCnt;
           _jiliType = std::move(_jili);
        });
    });

    // 停止激励
    connect(ui->actionJiLiStop, &QAction::triggered,[&](){

    });

    // 添加激励
    connect(ui->actionAddJiLi, &QAction::triggered,[&](){

    });

    // 系统设置
    connect(ui->actionSetDefault, &QAction::triggered, [&](){

    });
}

void MainWindow::statusBarRecvBytesCnt()
{
    statusBarReadBytesLabel->setText(QString::number(recvCnt));
}

void MainWindow::statusBarSendBytesCnt()
{
    statusBarWriteBytesLabel->setText(QString::number(sendCnt));
}

void MainWindow::displayReceiveData(const QByteArray &data)
{
    static QString s;
    s.clear();

    if(isShowData)
    {
        s.append("<font color=\"#0513fb\">[" + getTimestamp() + " R] </font>");

        if(isShowHexCode)
            s.append(dataToHex(data));
        else
            s.append(QString::fromLocal8Bit(data));

        ui->textBrowser->append(s);
    }
}

void MainWindow::displaySendData(const QByteArray &data)
{
    static QString s;
    s.clear();

    if(isShowData)
    {
        s.append("<font color=\"#49c21d\">[" + getTimestamp() + " T] </font>");

        if(isShowHexCode)
            s.append(dataToHex(data));
        else
            s.append(QString::fromLocal8Bit(data));

        ui->textBrowser->append(s);
    }

}
