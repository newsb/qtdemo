#include "mainscene.h"

MainScene::MainScene(QWidget *parent)
    : QWidget(parent)
{
    this->mBird=new Bird(this);
    mBird->setParent(this);

}

MainScene::~MainScene()
{
}

