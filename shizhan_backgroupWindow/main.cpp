#include "widget.h"

#include <QApplication>

#include "httptestwidget.h"
#include "mystrrequestwidget.h"

#include <QLabel>
#include <QScrollArea>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    HttpTestWidget w1;
    w1.show();

    MyStrRequestWidget w2;
    w2.show();

#if 0 //演示QScrollArea
     QLabel *imageLabel = new QLabel;
     QImage image(":/res/1.jpg");
     imageLabel->setPixmap(QPixmap::fromImage(image));
     QScrollArea *scrollArea = new QScrollArea;
     scrollArea->setBackgroundRole(QPalette::Dark);
     scrollArea->setWidget(imageLabel);
     scrollArea->show();
#endif

    return a.exec();
}
