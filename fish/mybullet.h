#ifndef MYBULLET_H
#define MYBULLET_H

#include "mypixmapitem.h"
#include <QGraphicsScene>

class MyBullet : public MyPixmapItem {

  public:
    MyBullet(const QString &filename, QGraphicsScene *scene, qreal angle);
    void doColliding();
    // QGraphicsItem interface
  public:
    virtual void advance(int phase) override;

  private:
    QGraphicsScene *mScene;

    // QGraphicsItem interface
  public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // BULLET_H
