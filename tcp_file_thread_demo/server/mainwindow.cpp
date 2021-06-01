#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
//#include "recvfilethread.h"
#include <QMessageBox>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("服务端");
    qDebug()<<"MainWindow::MainWindow currentThread:"<<QThread::currentThread();


    m_s=new QTcpServer(this);
    connect(m_s,&QTcpServer::acceptError,this,[=](QAbstractSocket::SocketError socketError){
       qCritical()<<"acceptError:"<<socketError << ";errorString:" <<m_s->errorString(); //TODO:如何转义socketError参数？？？m_s->errorString;
    });

    connect(m_s,&QTcpServer::newConnection,this,[=](){
        QTcpSocket *mSocket=m_s->nextPendingConnection();
        qDebug()<<"RecvFileThread::run currentThread:"<<QThread::currentThread()
               <<";current socket:"<<mSocket <<";socket.isOpen:"<<mSocket->isOpen();

        void(QTcpSocket::* signal1)(QAbstractSocket::SocketError)=&QTcpSocket::error;
        //auto signal1=QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::error);
        connect(mSocket,signal1 ,this,[=](QAbstractSocket::SocketError socketError){
            qDebug()<<"socket err:"<<socketError<<";socket.errorString:"<<mSocket->errorString();
        });

//        const int MAX_SIZE_READ=7*1024;

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

//QByteArray data=mSocket->readAll();
//mFile->write(data);
//mFile->waitForBytesWritten(100000);
//count+=data.size();
//qDebug() << "file write :" << data.size() ;

            while ( readSize<avaiSize){//(count<total){
                QByteArray data=mSocket->read(1024*7);
    //            if( data.isEmpty()){
    //                qDebug() <<"read isEmpty:"<<data.size();
    //                //count+=data.size();
    //                //break;//                continue;

    //            }
                readSize+=data.size();
                mFile->write(data);
                mFile->waitForBytesWritten(100000);
                count+=data.size();
                qDebug() << "file write :" << data.size()<<";  readSize="<<readSize;
            }
            qDebug() << "file end  count="<<count;

            if(count==total+255+4){
                //接收完了
                mFile->flush();
                mFile->close();
                mFile->deleteLater();
               // emit recvOver();

            }


        });

        qDebug() << "waitting recv data ... "  ;
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_btnStartListen_clicked()
{
    bool ok=false;
    quint16 port=ui->edtPort->text().toUInt(&ok);
    if(!ok) {qDebug()<<"  port err"; return;}

    if (m_s->isListening())
        return;

    ok=m_s->listen(QHostAddress::Any,port);
    if(!ok) {qDebug()<<"listen err"; return;}




}
