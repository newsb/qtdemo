#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include "filesend.h"

#include <QFile>
#include<QDateTime>
#include<QThread>
#include<QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("客户端");
    qDebug()<<"MainWindow  currentThread:"<<QThread::currentThread();
//    m_socket=new QTcpSocket(this);

    FileSend *fs=new FileSend();
    QThread *t=new QThread();
    fs->moveToThread(t);
    t->start();
    connect(this,&MainWindow::startConnect,fs,&FileSend::connectServer);
    connect(this,&MainWindow::startSendFile,fs,&FileSend::sendfile);
    connect(fs,&FileSend::connectOK,this,[=](){
        QMessageBox::information(this,"提示","连接服务器成功！");
    });
    connect(fs,&FileSend::sendOver,this,[=](){
       //发送完了
       t->quit();
       t->wait();
       t->deleteLater();
       fs->deleteLater();
       QMessageBox::information(this,"提示","发送完毕！");
    });
}

MainWindow::~MainWindow()
{
//    m_socket->close();
//    m_socket->deleteLater();

    delete ui;
}


void MainWindow::on_btnConnect_clicked()
{

    bool ok=false;
    quint16 port=ui->edtPort->text().toUInt(&ok);
    if(!ok) {
        qDebug()<<"  port err"; return;
    }
    QString ip=ui->edtIP->text();
    if(ip.isEmpty())
    {
        qDebug()<<"  ip err"; return;
    }

    emit startConnect(ip,port);

//    m_socket->connectToHost(ip,port);

//    connect(m_socket,&QTcpSocket::connected,this,[=](){
//        qInfo()<<"socket connected";
//    });
//    connect(m_socket,&QTcpSocket::disconnected,[=](){
//        qInfo()<<"socket disconected";
//        m_socket->close();
//        m_socket->deleteLater();

//    });



}

#include <QFileDialog>

void MainWindow::on_btnSelect_clicked()
{
    QString s=QFileDialog::getOpenFileName(this,"文件选择","",tr("{text File(*.txt)"));
    if(!s.isEmpty()){
        ui->edtPath->setText(s);
    }

}

void MainWindow::on_btnSend_clicked()
{
    QString path=ui->edtPath->text();

    if(path.isEmpty()){
        qDebug()<<" select file null";
        return;
    }
    emit startSendFile(path);
//    if(m_socket->ConnectedState!=QAbstractSocket::ConnectedState){
//        qDebug()<<" disconnected!"<<m_socket->ConnectedState;
//        return;
//    }

//    QFile file(path);
//    bool ok=file.open(QFile::ReadOnly);
//    if(!ok){
//        qDebug()<<" open file failed";
//        return;
//    }
//    QByteArray data=file.readAll();
//    m_socket->write(data);
//    m_socket->waitForBytesWritten();

}


