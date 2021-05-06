#include "mycountthreadwork.h"

MyCountThreadWork::MyCountThreadWork(QObject *parent) : QObject(parent)
{

}

#include <QDebug>
#include <QThread>
void MyCountThreadWork::working() {
    qDebug() << "当前线程MyCountThreadWork对象的地址: " << QThread::currentThread();

    int num = 0;
    while(1)
    {
        emit curNumber(num++);
        if(num == 100000)
        {
            break;
        }
        QThread::usleep(1);
    }
    qDebug() << "MyCountThreadWork::run() 执行完毕, 子线程退出...";
}
