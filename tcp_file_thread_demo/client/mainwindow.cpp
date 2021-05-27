#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("客户端");
    m_socket=new QTcpSocket(this);
}

MainWindow::~MainWindow()
{
    m_socket->close();
    m_socket->deleteLater();

    delete ui;
}

#include <QFile>
#include<QDateTime>


void MainWindow::on_btnConnect_clicked()
{

    bool ok=false;
    quint16 port=ui->edtPort->text().toUInt(&ok);
    if(!ok) {qDebug()<<"  port err"; return;}
    QString ip=ui->edtIP->text();
    if(ip.isEmpty()) {qDebug()<<"  ip err"; return;}

    m_socket->connectToHost(ip,port);

    connect(m_socket,&QTcpSocket::connected,this,[=](){
        qInfo()<<"socket connected";
    });
    connect(m_socket,&QTcpSocket::disconnected,[=](){
        qInfo()<<"socket disconected";
        m_socket->close();
        m_socket->deleteLater();

    });

    void(QTcpSocket::* signal1)(QAbstractSocket::SocketError)=&QTcpSocket::error;
//    auto signal1=QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error);
    connect(m_socket,signal1 ,this,[=](QAbstractSocket::SocketError socketError){
        qCritical()<<"socket err:"<<socketError;
    });

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
    QString mPath=ui->edtPath->text();

    if(mPath.isEmpty()){
        qDebug()<<" select file null";
        return;
    }

    if(m_socket->ConnectedState!=QAbstractSocket::ConnectedState){
        qDebug()<<" disconnected!"<<m_socket->ConnectedState;
        return;
    }

    QFile file(mPath);
    bool ok=file.open(QFile::ReadOnly);
    if(!ok){
        qDebug()<<" open file failed";
        return;
    }
    QByteArray data=file.readAll();
    m_socket->write(data);
    m_socket->waitForBytesWritten();

}
