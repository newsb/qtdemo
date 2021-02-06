#include "bird.h"

Bird::Bird(QWidget *parent) : QWidget(parent)
{
    for (int i=0;i<30;i++){
        QString str= QString(":/res/gif_0.png").arg(i);
        mPix.load(str);
    }

}

void Bird::paintEvent(QPaintEvent *event)
{

}
