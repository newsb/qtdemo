#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("服务端");

    m_s=new QTcpServer();
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

    ok=m_s->listen(QHostAddress::Any,port);
    if(!ok) {qDebug()<<"listen err"; return;}

    connect(m_s,&QTcpServer::acceptError,this,[=](QAbstractSocket::SocketError socketError){
       qCritical()<<"acceptError:"<<socketError << ";errorString:" <<m_s->errorString(); //TODO:如何转义socketError参数？？？m_s->errorString;
    });

    connect(m_s,&QTcpServer::newConnection,this,[=](){
        QTcpSocket *socket=m_s->nextPendingConnection();
        qInfo()<<"newConnection(" <<socket <<") :peerName:"<< socket->peerName()<<"peer prot:"<<socket->peerPort();


//        static qint64 total=0;

        //写入磁盘文件
//qDebug()<<"data size: "<<data.size() ;

        connect(socket,&QTcpSocket::readyRead,this,[=](){
//            qInfo()<<"socket readyRead";

//            QByteArray data;
//            data.append();
//            total+=data.size();


            QString mFileName=QDateTime::currentDateTime().toString("yyyy-MM-dd-hhmmss")+".txt";

            QFile file(mFileName);
            bool ret= file.open(QFile::WriteOnly);
            if( ret){
                file.write( socket->readAll());
//                file.seek(total);
//                qDebug()<<"file name: "<<mFileName<<";size=" <<file.size()<<";pos="<<file.pos()<<";total="<<total;
                file.waitForBytesWritten(3000);
                file.flush();
                file.close();
            }

        });

        connect(socket,&QTcpSocket::connected,this,[=](){
            qInfo()<<"socket connected";
        });
        connect(socket,&QTcpSocket::disconnected,[=](){


            qInfo()<<"socket disconected";
            socket->close();
            socket->deleteLater();

        });

//         void(QTcpSocket::* signal1)(QAbstractSocket::SocketError)=&QTcpSocket::error;
        auto signal1=QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error);
        connect(socket,signal1 ,this,[=](QAbstractSocket::SocketError socketError){
            qCritical()<<"socket err:"<<socketError;
        });


    });
}
