#include "widget.h"

#include <QApplication>

#include <QHash>
#include <QByteArray>
#include <QStringList>

int main(int argc, char *argv[])
{
//    当一个signal被放到队列中（queued）时，它的参数(arguments)也会被一起一起放到队列中（queued起来），
//    这就意味着参数在被传送到slot之前需要被拷贝、存储在队列中（queue）中；为了能够在队列中存储这些参数(argument)，
//            Qt需要去construct、destruct、copy这些对象，而为了让Qt知道怎样去作这些事情，
//            参数的类型需要使用qRegisterMetaType来注册（如错误提示中的说明）
//https://blog.csdn.net/wadfji/article/details/54406767

    //    自己定义的类型如果想使用signal/slot来传递的话，则qRegisterMetaType注册
    qRegisterMetaType<QHash<QByteArray,QStringList>>("QHash<QByteArray,QStringList>");


    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
