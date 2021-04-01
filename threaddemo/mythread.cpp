#include "mythread.h"
#include <QDebug>

MyThread::MyThread() {}

void MyThread::run() {
    for (int i = 0; i < 10; i++) {
        qDebug() << i << i << i << i << i << i << i << i << i << i;
    }
}
