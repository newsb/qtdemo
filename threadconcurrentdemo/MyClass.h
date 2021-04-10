#ifndef MYCLASS_H
#define MYCLASS_H
#include <QtCore>//包含了QtCore，就不用再一个个的包含其他的了

//#include <QObject>
//#include <QDebug>
//#include <QThread>

class Receiver : public QObject
{
    Q_OBJECT

public slots:
    void onReceive(){
        qDebug()<<"currentThread:"<<QThread::currentThread() ;
    }
};
class Sender : public QObject
{
    Q_OBJECT
signals:
    void mySignal();
public slots:
    void helloThreadSlot(){
         qDebug()<<"helloThreadSlot :"<<QThread::currentThread() ;
    };

};
#endif // MYCLASS_H
