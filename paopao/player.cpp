#include "player.h"
#include "global.h"
#include <QDebug>

Player::Player(QGraphicsItem *parent) : QGraphicsItem(parent)
{

    QPixmap * pix;
    pix=new QPixmap(":/res/player.png");
    pix_width=pix->width();
    pix_height=pix->height();

     pixLeft= pix->copy(0,0,pix_width/4,pix_height).scaled(WALL_BRICK_SIZE,WALL_BRICK_SIZE);
     pixFront= pix->copy(1*pix_width/4,0,pix_width/4,pix_height).scaled(WALL_BRICK_SIZE,WALL_BRICK_SIZE);
     pixRight= pix->copy(2*pix_width/4,0,pix_width/4,pix_height).scaled(WALL_BRICK_SIZE,WALL_BRICK_SIZE);
     pixBack= pix->copy(3*pix_width/4,0,pix_width/4,pix_height).scaled(WALL_BRICK_SIZE,WALL_BRICK_SIZE);
    delete pix;

    mPix=new QPixmap(pixFront);
    mCurrentPostion=QPoint(220,220);
    setPos(mCurrentPostion);
#if 0
    ATTR x=attrAt(-1,-1);
    if(x==SPACE){
        qDebug()<<"x==SPACE";
    }else if(x==BRICK){
        qDebug()<<"x==BRICK";
     }else if(x==WALL){
        qDebug()<<"x==WALL";
     }else{
        qDebug()<<"x=="<<x;
    }
#endif
}

Player::~Player()
{
    delete mPix;
}




QRectF Player::boundingRect() const
{
    return QRectF(0,0,mPix->width(),mPix->height());
}

void Player::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(option);
    Q_UNUSED(widget);
    painter->drawPixmap(0,0,*mPix);
}
