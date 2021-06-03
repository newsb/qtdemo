#include "filesend.h"
#include <QDebug>
#include <QFile>
#include <QNetworkProxy>

#include <QThread>

FileSend::FileSend(QObject *parent) : QObject(parent)
{
}

void FileSend::connectServer(QString ip, quint16 port,bool useProxy,int proxyType,QString proxyIp,quint16 proxyPort,QString proxyUsr,QString proxyPwd)
{
    Q_UNUSED(proxyType);
    Q_UNUSED(proxyPwd);
    Q_UNUSED(proxyIp);
    Q_UNUSED(proxyPort);
    Q_UNUSED(proxyUsr);
    //todo:add proxy!!!
    qDebug()<<"FileSend::connectServer currentThread:"<<QThread::currentThread();
    mSocket=new QTcpSocket(this);

    if(useProxy){
        QNetworkProxy::ProxyType type=QNetworkProxy::NoProxy;
        if(proxyType==1){
            type=QNetworkProxy::HttpProxy;
        }else if(proxyType==2){
            type=QNetworkProxy::Socks5Proxy;
        }
        mSocket->setProxy(QNetworkProxy(type,proxyIp,proxyPort,proxyUsr,proxyPwd));
    }

    mSocket->connectToHost(ip,port);

    connect(mSocket,&QTcpSocket::connected,this,&FileSend::connectOK);

    connect(mSocket,&QTcpSocket::disconnected,[=](){
        qInfo()<<"socket disconected";
        mSocket->close();
        mSocket->deleteLater();
        emit connectBreak();
    });
//    connect(mSocket,&QTcpSocket::stateChanged,this,[=](QTcpSocket::SocketState socketState){
//        if (socketState==QTcpSocket::ConnectedState){
//            emit connectOK();
//        }else if(socketState==QTcpSocket::UnconnectedState){
//            emit connectBreak();
//        }
//    });

    void(QTcpSocket::* signal1)(QAbstractSocket::SocketError)=&QTcpSocket::error;
//    auto signal1=QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error);
    connect(mSocket,signal1 ,this,[=](QAbstractSocket::SocketError socketError){
        qCritical()<<"socket err:"<<socketError;
        mSocket->disconnectFromHost();
    });

//    if (mSocket->waitForConnected(-1))
//        qDebug("Connected!");
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
        int writenSize=mSocket->write(line);
        qDebug()<<"writenSize:"<<writenSize;
        //！！！不加上waitForBytesWritten，则服务端不触发或很少触发readyRead信号！~
        //但接收时不需要调用mFile->waitForBytesWritten函数。。
        mSocket->waitForBytesWritten();
//        QThread::usleep(800);
    }

    emit sendOver();
}

void FileSend::onTestProxyConnection(QString proxyIp, quint16 proxyPort, QString proxyUsr, QString proxyPwd)
{
    Q_UNUSED(proxyIp);
    Q_UNUSED(proxyPort);
    Q_UNUSED(proxyUsr);
    Q_UNUSED(proxyPwd);
}
