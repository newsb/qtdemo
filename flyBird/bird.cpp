#include "bird.h"
#include <QDebug>

Bird::Bird(QWidget *parent) : QWidget(parent)
{
    for (int i=0;i<30;i++){
        QString str= QString(":/res/gif_%1.png").arg(i);
        bool ret=mPix.load(str);
        if (!ret){
            qDebug()<<"load image failed:"<<str;
        }
    }
    this->setFixedSize(mPix.width(),mPix.height());

    this->mTimer=new QTimer(this);
    connect(mTimer,&QTimer::timeout,[=](){
         QString str= QString(":/res/gif_%1.png").arg(min++);
         this->mPix.load(str);

         if (this->min>this->max){
             this->min=0;
         }

         emit changePix();
    });
}

void Bird::running()
{
    this->mTimer->start(50);
}

void Bird::mousePressEvent(QMouseEvent *event)
{
    m_pos=event->globalPos() - ((QWidget*)(this->parent()))->frameGeometry().topLeft();
}

void Bird::mouseMoveEvent(QMouseEvent *event)
{
    //获取到窗口移动的位置
    emit moving(event->globalPos()-this->m_pos);
}

