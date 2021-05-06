#include "mycountthread.h"

MyCountThread::MyCountThread(QObject *parent) : QThread(parent)
{

}

#include <QDebug>

void MyCountThread::run()
{
    qDebug() << "当前线程MyCountThread对象的地址: " << QThread::currentThread();

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
    qDebug() << "MyCountThread::run() 执行完毕, 子线程退出...";

/*
作者: 苏丙榅
链接: https://subingwen.cn/qt/thread/#2-2-%E7%A4%BA%E4%BE%8B%E4%BB%A3%E7%A0%81
来源: 爱编程的大丙
    著作权归作者所有。商业转载请联系作者获得授权，非商业转载请注明出处。*/
}
