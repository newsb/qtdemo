#include "cell.h"

Cell::Cell(ATTR attr,int row,int col,QGraphicsItem *parent):
    QGraphicsItem(parent),
    mRow(row),
    mCol(col),
    mAttr(attr)
{

}


QRectF Cell::boundingRect() const
{
    return QRectF(mCol*WALL_BRICK_SIZE,mRow*WALL_BRICK_SIZE,WALL_BRICK_SIZE,WALL_BRICK_SIZE);
}
#include <QPainter>
void Cell::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(painter);
    Q_UNUSED(option);
    Q_UNUSED(widget);
    switch (mAttr) {
    case WALL:
        painter->drawPixmap(rowCol2Coordinate(mRow,mCol),QPixmap(":/res/wall.jpg").scaled(WALL_BRICK_SIZE,WALL_BRICK_SIZE));
        break;
    case BRICK:
        painter->drawPixmap(rowCol2Coordinate(mRow,mCol),QPixmap(":/res/brick.jpg").scaled(WALL_BRICK_SIZE,WALL_BRICK_SIZE));
        break;
    case SPACE:
    case BUBBLE:
        painter->drawPixmap(rowCol2Coordinate(mRow,mCol),QPixmap(":/res/space.jpg").scaled(WALL_BRICK_SIZE,WALL_BRICK_SIZE));
        break;
    default:
//                qDebug()<<"errval :map[r][c]="<<map[r][c];
         break;
    }
}
