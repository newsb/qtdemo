#ifndef GUN_H
#define GUN_H

#include "mypixmapitem.h"
#include <QGraphicsScene>
#include <QPixmap>

class Gun : public MyPixmapItem {
  public:
    Gun(const QString &filename, QGraphicsScene *scene);

    //  private:
    //    QPixmap pix;

    // QGraphicsItem interface
    //  public:
    //    virtual QRectF boundingRect() const override;
    //    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // GUN_H
