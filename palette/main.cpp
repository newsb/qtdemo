#include "palettedialog.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PaletteDialog w;
    w.show();
    return a.exec();
}
