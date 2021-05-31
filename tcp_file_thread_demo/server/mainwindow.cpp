#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "recvfilethread.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("服务端");
    qDebug()<<"MainWindow::MainWindow currentThread:"<<QThread::currentThread();


    m_s=new QTcpServer(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

#include <QFile>
#include<QDateTime>

void MainWindow::on_btnStartListen_clicked()
{
    bool ok=false;
    quint16 port=ui->edtPort->text().toUInt(&ok);
    if(!ok) {qDebug()<<"  port err"; return;}

    if (m_s->isListening())
        return;

    ok=m_s->listen(QHostAddress::Any,port);
    if(!ok) {qDebug()<<"listen err"; return;}


    connect(m_s,&QTcpServer::newConnection,this,[=](){
        QTcpSocket *socket=m_s->nextPendingConnection();

        qDebug()<<"newConnection socket:"<<socket;
        //创建子线程
        RecvFileThread *subThread=new RecvFileThread(socket);
        connect(subThread,&RecvFileThread::recvOver,this,[=](){
           qDebug()<<"RecvFileThread::recvOver "; //接收文件完成，退出
            subThread->exit();
            subThread->wait();
            subThread->deleteLater();
            socket->close();
            socket->deleteLater();
            QMessageBox::information(this,"提示","接收完毕！");
        });

        subThread->start();
    });

    connect(m_s,&QTcpServer::acceptError,this,[=](QAbstractSocket::SocketError socketError){
       qCritical()<<"acceptError:"<<socketError << ";errorString:" <<m_s->errorString(); //TODO:如何转义socketError参数？？？m_s->errorString;
    });


//    connect(socket,&QTcpSocket::disconnected,[=](){


//        qInfo()<<"socket disconected";
//        socket->close();
//        socket->deleteLater();

//    });

//          void(QTcpSocket::* signal1)(QAbstractSocket::SocketError)=&QTcpSocket::error;
//    auto signal1=QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error);
//    connect(socket,signal1 ,this,[=](QAbstractSocket::SocketError socketError){
//        qCritical()<<"socket err:"<<socketError;
//    });

}
