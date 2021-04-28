#include "clipboarddemo.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ClipboardDemo w;
    w.show();
    return a.exec();
}
