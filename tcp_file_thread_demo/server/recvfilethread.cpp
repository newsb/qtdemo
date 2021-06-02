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

    void(QTcpSocket::* signal1)(QAbstractSocket::SocketError)=&QTcpSocket::error;
    //auto signal1=QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error);
    connect(mSocket,signal1 ,this,[=](QAbstractSocket::SocketError socketError){
        qDebug()<<"socket err:"<<socketError<<";socket.errorString:"<<mSocket->errorString();
    });

    const int MAX_SIZE_READ=7*1024;

    connect(mSocket,&QTcpSocket::readyRead,this,[=](){
        int avaiSize=mSocket->bytesAvailable();
        qDebug() <<"readyRead--------------bytesAvailable:"<< avaiSize;

        static bool ret=false;
        static int count=0;
        static int total=0;

        int readSize=0;
        if (count==0){
            mSocket->read((char *)&total,4);//先接收头4位文件大小
            qDebug() <<"read file size:"<< total;
            count+=4;

            QByteArray fndata=mSocket->read(255 );
            count+=255;
            QString fn=QString(fndata);
            qDebug() <<"read fn:"<< fn;

            readSize+=4;
            readSize+=255;

            mFile=new QFile(fn);
            ret= mFile->open(QFile::WriteOnly);
            if( !ret){
                qDebug() <<"open fn failed";
                return;
            }

            if( mFile==nullptr|| !mFile->isOpen()|| !mFile->isWritable()){
                qDebug() <<"mFile is nullptr or  not isOpen or not isWritable";
                return;
            }
        }
        QByteArray data=mSocket->readAll();
        mFile->write(data);

        //！！！不加上waitForBytesWritten，则服务端不触发或很少触发readyRead信号！~
        //但接收时不需要调用mFile->waitForBytesWritten函数。。
        //mFile->waitForBytesWritten(100000);//
        count+=data.size();
        qDebug() << "file write :" << data.size() ;
        int per=count*100/(total+255+4) ;
        emit progressChanged(per);

//分块接收
//        while ( readSize<avaiSize){//(count<total){
//            QByteArray data=mSocket->read(MAX_SIZE_READ);
//            readSize+=data.size();
//            mFile->write(data);
//            //！！！不加上waitForBytesWritten，则服务端不触发或很少触发readyRead信号！~
//            //但接收时不需要调用mFile->waitForBytesWritten函数。。
// //            mFile->waitForBytesWritten(100000);
//            count+=data.size();
//            qDebug() << "file write :" << data.size()<<";  readSize="<<readSize;
//        }

        qDebug() << "file end  count="<<count;
        if(count==total+255+4){
            //接收完了
            mFile->flush();
            mFile->close();
            mFile->deleteLater();
            emit recvOver();

        }




    });

    qDebug() << "waitting recv data ... "  ;
    //启动时间循环卡住run方法，否则线程一下子退出了
    exec();

     qDebug() << "recv thread done  "  ;
}
