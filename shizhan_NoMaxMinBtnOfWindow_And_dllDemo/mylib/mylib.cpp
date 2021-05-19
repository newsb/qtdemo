#include "mylib.h"
#include <QMessageBox>
#include <QDebug>

Mylib::Mylib()
{
    QMessageBox::information(nullptr,"tt1","msg from dll class");
}
void testfun()
{
    qDebug() <<"msg from dll.testfun";
}
