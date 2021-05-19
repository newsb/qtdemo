#include "dialog.h"
#include "mywidget.h"
#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    myWidget w1;
    w1.show();
    MainWindow w2;
    w2.show();
    return a.exec();
}
