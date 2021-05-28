#include "recvfilethread.h"

RecvFileThread::RecvFileThread(QTcpSocket * socket,QObject *parent) : QThread(parent)
{
    mSocket=socket;
}

#include <QFile>
//#include<QDateTime>

void RecvFileThread::run()
{
//    QString fileName=QDateTime::currentDateTime().toString("yyyy-MM-dd-hhmmss")+".txt";

        QFile *file=nullptr;
        connect(mSocket,&QTcpSocket::readyRead,this,[=,&file](){
            static bool ret=false;
            static int count=0;
            static int total=0;

//            QString fn=file->fileName();//QFile::fileName()返回不包含路径的文件名
//            char * buf=new char(4);

//            char * cfn=fn.data();
            if (count==0){
                mSocket->read((char *)&total,4);//先接收头4位文件大小
                qDebug() <<"read file size:"<< total;

                QByteArray fndata=mSocket->read(255 );
                QString fn=QString(fndata);
                qDebug() <<"read fn:"<< fn;

                file=new QFile(fn);
                ret= file->open(QFile::WriteOnly);
            }

            if( !ret){
                qDebug() <<"open fn failed";
                return;
            }

            //读取剩余数据
            QByteArray data=mSocket->readAll();
            count+=data.size();
            file->write( data);
            if(count==total){
                //接收完了
                file->close();
                file->deleteLater();
                emit recvOver();
            }
        });
    //启动时间循环卡住run方法，否则线程一下子退出了
    exec();
}
