#include "mywidget.h"

#include "mylib/mylib.h"

myWidget::myWidget(QWidget *parent) : QWidget(parent)
{
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);

    Mylib lib;
    testfun();
}
