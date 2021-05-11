#ifndef CELL_H
#define CELL_H

#include <QGraphicsItem>
#include "global.h"

class Cell : public QGraphicsItem
{
public:
    Cell(ATTR attr,int row,int col,QGraphicsItem *parent = nullptr);

    int mRow,mCol;
    ATTR mAttr=UNDEFINE;

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // CELL_H
