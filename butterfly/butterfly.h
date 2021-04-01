#ifndef BUTTERFLY_H
#define BUTTERFLY_H

#include <QGraphicsItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QObject>
#include <QPainter>

class Butterfly : public QObject, public QGraphicsItem {
    Q_OBJECT
  public:
    explicit Butterfly(QObject *parent = nullptr);
    //定时器实现动画，再timerEvent事件中重绘QGraphicsItem
    virtual void timerEvent(QTimerEvent *event) override;
    //限制图元的区域继承自QGriaphicsItem的图元必须实现的函数
    virtual QRectF boundingRect() const override;
  signals:

    // QGraphicsItem interface
  public:
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

  private:
    //标识蝴蝶翅膀位置
    bool up;
    QPixmap pix_up;
    QPixmap pix_down;
    qreal angle;
};

#endif // BUTTERFLY_H
