#include "mymd5.h"

MyMd5::MyMd5(QObject *parent) : QObject(parent)
{

}
#include <QCryptographicHash>
#include <QFile>
#include <QDebug>

QByteArray MyMd5::getFileMd5(const QString &filename)
{
    QByteArray md5val;
    QFile file(filename);
    if(file.open(QIODevice::ReadOnly)){
        QCryptographicHash md5(QCryptographicHash::Md5);
        while(!file.atEnd()){
            QByteArray content=file.read(100*1024*1024);
            md5.addData(content);
            //不让界面卡死
//            qApp->processEvents();
        }
        md5val=md5.result();
        qDebug()<<md5val<<":"<<md5val.toHex();
    }
    file.close();

    return md5val.toHex();
}

void MyMd5::onStartCalcMd5(QStringList files)
{
    QHash<QByteArray,QStringList> duplicationList;
    for(int i=0;i<files.count();i++){
        QString filename=files.at(i);
        QByteArray md5=getFileMd5(filename);

        duplicationList[md5].append(filename);
        emit progress_changed(i+1);//ui->progressBar->setValue(i+1);
    }

    emit calcMd5Finished(duplicationList);
}
