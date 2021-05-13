#include "widget.h"

#include <QApplication>

#include <QHash>
#include <QByteArray>
#include <QStringList>

int main(int argc, char *argv[])
{
    qRegisterMetaType<QHash<QByteArray,QStringList>>("QHash<QByteArray,QStringList>");


    QApplication a(argc, argv);
    Widget w;
    w.show();
    return a.exec();
}
