#include "SelectWidget.h"

#include <QMessageBox>
#include <QVBoxLayout>

SelectWidget::SelectWidget(QWidget *parent)
    : QWidget(parent) {

    setFixedSize(800, 600);

    mFont.setFamily("华康少女文字W5(P)");
    mFont.setBold(true);
    mFont.setWeight(56);


//    bg = new QLabel(this);
//    bg->setGeometry(0, 0, 800, 600);
//    bg->setPixmap(QPixmap(":/res/bg.jpg").scaled(this->width(), this->height()));

    QVBoxLayout *layout = new QVBoxLayout;

    bgTitle = new QLabel(this);
    bgTitle->setGeometry(0, 0, 400, 145);
//    bgTitle->setText("中国象棋");
//    bgTitle->setFont(mFont);
    bgTitle->setPixmap(QPixmap(":/res/2.png").scaled(400, 145));
    bgTitle->move(this->width() / 2 - bgTitle->width() / 2, 30);
    this->setStyleSheet("* {font-family: 华康少女文字W5(P);font-size: 56px;color: #f16c4d;bold: true}");
    initBtns();

    //    layout->addWidget(bgTitle);

    //    layout->addSpacing(77);
    layout->addWidget(btnBase);
    layout->addWidget(btnSingle);
    layout->addWidget(btnNet);
    layout->setAlignment(Qt::AlignBottom);
    layout->setMargin(20);
    layout->setSpacing(20);

    //    layout->setGeometry(QRect(300, 160, 200, 107));
    this->setLayout(layout);


#if 0
    /**thread two**/
    MyTask* worker = new MyTask();
    worker->moveToThread(&workerThread);

    //在线程创建之后，这个QObject的销毁不应该在主线程里进行，而是通过deleteLater槽进行安全的销毁
    //QThread::finished信号对接QObject的deleteLater使得线程结束后，继承QObject的那个多线程类会自己销毁
    //QThread::finished信号对接QThread自己的deleteLater，这个不是必须，下面官方例子就没这样做
    //把线程的finished信号和object的deleteLater槽连接，这个信号槽必须连接，否则会内存泄漏
    connect(&workerThread,&QThread::finished,worker,&QObject::deleteLater);
    //正常连接其他信号和槽（在连接信号槽之前调用moveToThread，不需要处理connect的第五个参数，
    //否则就显示声明用Qt::QueuedConnection来连接）
    connect(this,&SelectWidget::operate,worker,&MyTask::doTask);
    connect(worker,&MyTask::resultReady,this,&SelectWidget::handleResults);
    //初始化完后调用'QThread::start()'来启动线程
    workerThread.start();

    emit operate("USB");
#endif
}


void SelectWidget::handleResults(const QString &result)
{
    qDebug()<<"do task end,result="<<result ;
}


void SelectWidget::initBtns() {
    btnBase = new QPushButton(this);
    btnBase->setFlat(true);
    btnBase->setText("基本模式");
    btnBase->setGeometry(22, 22, 88, 44);
    btnBase->setFont(mFont);
    connect(btnBase, &QPushButton::clicked, [=]() {
        _borad = new MyWidget();

        connect(_borad,&MyWidget::back_signal,[=](){
            _borad->close();
            this->show();
        });
        _borad->show();
        this->hide();
    });

    btnSingle = new QPushButton(this);
    btnSingle->setFlat(true);
    btnSingle->setText("单人模式");
    btnSingle->setGeometry(22, 66, 88, 44);
    btnSingle->setFont(mFont);
    connect(btnSingle, &QPushButton::clicked, [=]() {
        _borad = new SingleGame();
        connect(_borad,&SingleGame::back_signal,[=](){
            _borad->close();
            this->show();
        });
        _borad->show();
        this->hide();
    });

    btnNet = new QPushButton(this);
    btnNet->setFlat(true);
    btnNet->setText("网络模式");
    btnNet->setGeometry(22, 22, 110, 44);
    btnNet->setFont(mFont);
    connect(btnNet, &QPushButton::clicked, [=]() {
        //    网络 + 2人
        bool bServer = false;
        QMessageBox::StandardButton ret = QMessageBox::question(nullptr, "server or client?", "作为服务器启动？");
        if (ret == QMessageBox::Yes) {
            bServer = true;
        }
        _borad = new NetGame(bServer);
        connect(_borad,&NetGame::back_signal,[=](){
            _borad->close();
            this->show();
        });
        _borad->show();
        this->hide();
    });
}


