#include "food.h"
#include <QPainter>

#include "constants.h"

static const qreal FOOD_RADIUS = 3;

Food::Food(qreal x, qreal y)
{
    setPos(x, y);
    //setData为该图形元素添加额外的数据信息，类似于散列一样的键值对的形式。
    //QGraphicsItem::setData()以键值对的形式设置元素的自定义数据。
    //在Food的构造函数中，将GD_Type的值设置为GO_Food。
    //那么，这里我们取出GD_Type，如果其值是GO_Food，
    //意味着这个QGraphicsItem就是一个Food，因此我们可以将其安全地进行后面的类型转换
    setData(GD_Type, GO_Food);
}
//由于我们的元素就是一个圆形，所以我们返回的是一个简单的矩形。
//注意，这个矩形的范围实际是四倍于实际区域的：以元素坐标 (x, y) 为中心，边长为TILE_SIZE * 2的正方形。
QRectF Food::boundingRect() const
{
    return QRectF(-TILE_SIZE,    -TILE_SIZE,
                  TILE_SIZE * 2, TILE_SIZE * 2 );
}
//由于设置了shape()函数，paint()反而更简单。我们所要做的，就是把shape()函数定义的路径绘制出来。
void Food::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);
    painter->fillPath(shape(), Qt::red);

    painter->restore();
}
//这个函数返回的是元素实际的路径
//所谓路径，可以理解成元素的矢量轮廓线，就是QPainterPath所表示的。
//我们使用addEllipse()函数，添加了一个圆心为 (TILE_SIZE / 2, TILE_SIZE / 2)，半径 FOOD_RADIUS 的圆，其范围是左上角为 (x, y) 的矩形。
QPainterPath Food::shape() const
{
    QPainterPath p;
    p.addEllipse(QPointF(TILE_SIZE / 2, TILE_SIZE / 2), FOOD_RADIUS, FOOD_RADIUS);
    return p;
}
