#include "mainscene.h"
#include <QPainter>

MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
{
//    setWindowIcon()
    this->mBird=new Bird(this);
    mBird->setParent(this);
    this->setFixedSize(this->mBird->width(),mBird->height());

    connect(mBird,&Bird::changePix,[=](){
        update();
    });

    this->mBird->running();

    //
    connect(mBird,&Bird::moving,[=](QPoint point){
        this->move(point);
    });
}

MainScene::~MainScene()
{
}

void MainScene::paintEvent(QPaintEvent *)
{
    QPainter p(this);
    p.drawPixmap(0,0,this->mBird->mPix);
}

