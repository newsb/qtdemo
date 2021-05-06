#include "mainwindow.h"
#include <iostream>
#include <QThread>
#include <QtConcurrent>
#include <QApplication>
#include "mywidget.h"

void printMes(const char*mes)
{
    std::cout<<"pprintMes(char*mes) thread :"<<QThread::currentThreadId()<<std::endl;
    std::cout<<mes<<std::endl;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    std::cout<<"mainthread:"<<QThread::currentThreadId()<<std::endl;
    const char* mes= "hello world";
    QtConcurrent::run(printMes,mes);

    MainWindow w;
    w.show();

    MyWidget mw;
    mw.show();

    return a.exec();
}
