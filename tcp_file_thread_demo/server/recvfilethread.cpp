#include "recvfilethread.h"

RecvFileThread::RecvFileThread(QTcpSocket * socket,QObject *parent) : QThread(parent)
{
    mSocket=socket;


    mFile=nullptr;

}


void RecvFileThread::run()
{
//    QString fileName=QDateTime::currentDateTime().toString("yyyy-MM-dd-hhmmss")+".txt";

    qDebug()<<"RecvFileThread::run currentThread:"<<QThread::currentThread()
           <<";current socket:"<<mSocket
           <<";socket.isOpen:"<<mSocket->isOpen();


    connect(mSocket,&QTcpSocket::readyRead,this,[=](){
        qDebug() <<"readyRead--------------bytesAvailable:"<< mSocket->bytesAvailable();

        /*static bool ret=false;
        static int count=0;
        static int total=0;

        if (count==0){
            mSocket->read((char *)&total,4);//先接收头4位文件大小
            qDebug() <<"read file size:"<< total;

            QByteArray fndata=mSocket->read(255 );
            QString fn=QString(fndata);
            qDebug() <<"read fn:"<< fn;

            mFile=new QFile(fn);
            ret= mFile->open(QFile::WriteOnly);
        }
        if( !ret){
            qDebug() <<"open fn failed";
            return;
        }

        if( mFile==nullptr|| !mFile->isOpen()|| !mFile->isWritable()){
            qDebug() <<"mFile is nullptr or  not isOpen or not isWritable";
            return;
        }

        //读取剩余数据
        QByteArray data=mSocket->readAll();

        if( data.isEmpty()){
            qDebug() <<"readAll isEmpty";
            return;
        }

        count+=data.size();
        mFile->write(data);
        qDebug() << "file write :" << data.size();
        if(count==total){
            //接收完了
            mFile->flush();
            mFile->close();
            mFile->deleteLater();
            emit recvOver();
        }*/
    });

    qDebug() << "waitting recv data ... "  ;
    //启动时间循环卡住run方法，否则线程一下子退出了
    exec();

     qDebug() << "recv thread done  "  ;
}
