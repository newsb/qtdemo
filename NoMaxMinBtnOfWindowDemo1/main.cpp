#include "dialog.h"
#include "mywidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Dialog w;
    w.show();
    myWidget w1;
    w1.show();
    return a.exec();
}
