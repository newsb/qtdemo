#include "mytask.h"
#include <QDebug>
#include <unistd.h>
MyTask::MyTask(QObject *parent): QObject(parent)
{

}

void MyTask::doTask(const QString &parameter)
{
    QString result="done!";

    static int x=0;
    while (x<10)
    {
        qDebug()<<"do task parameter:"<<parameter<<" -->"<<x;
        sleep(2);
        x++;
    }

    /* ... here is the expensive or blocking operation ... */
    emit resultReady(result);
}
