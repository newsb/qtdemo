#include "filesend.h"
#include <QDebug>
#include <QFile>

#include <QThread>

FileSend::FileSend(QObject *parent) : QObject(parent)
{
}

void FileSend::connectServer(QString ip, quint16 port)
{
    qDebug()<<"FileSend::connectServer currentThread:"<<QThread::currentThread();
    mSocket=new QTcpSocket(this);
    mSocket->connectToHost(ip,port);

    connect(mSocket,&QTcpSocket::connected,this,&FileSend::connectOK);

    connect(mSocket,&QTcpSocket::disconnected,[=](){
        qInfo()<<"socket disconected";
        mSocket->close();
        mSocket->deleteLater();
        emit connectBreak();
    });

    void(QTcpSocket::* signal1)(QAbstractSocket::SocketError)=&QTcpSocket::error;
//    auto signal1=QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error);
    connect(mSocket,signal1 ,this,[=](QAbstractSocket::SocketError socketError){
        qCritical()<<"socket err:"<<socketError;
        mSocket->disconnectFromHost();
    });
}

#include <QFileInfo>
void FileSend::sendfile(QString filePath)
{
    qDebug()<<"FileSend::sendfile currentThread:"<<QThread::currentThread();
    QFile file(filePath);
    bool ok=file.open(QFile::ReadOnly);
    if(!ok){
        qDebug()<<" open file failed";
        return;
    }

    QFileInfo info(file);


    while(!file.atEnd()){
        static qint64 num=0;
        QString fn=info.fileName();
        int fileSize=info.size();

        if(num==0){
            mSocket->write((char*)&fileSize,4);//第一次发送文件大小过去
            qDebug() <<"write file size:"<< fileSize;
            mSocket->write(fn.toUtf8(),255);
            qDebug() <<"write fn:"<< fn;
        }
//        QByteArray line=file.readLine();
        QByteArray line=file.read(1024*7);
        qint64 len=line.size();
        num+=len;
        int per=num*100/fileSize ;
        emit progressChanged(per);
        mSocket->write(line);
//        mSocket->waitForBytesWritten();
        QThread::usleep(800);
    }

    emit sendOver();
}
