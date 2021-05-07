#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsItem>
#include <QPixmap>

#include <QPainter>
class Player : public QGraphicsItem
{

public:
    explicit Player(QGraphicsItem *parent = nullptr);
    ~Player();
    enum Direction{UP,DOWN,LEFT,RIGHT};
    bool walkAStep(Direction direct);
    void putBubble();
    const int STEP_UNIT=20;
signals:
private:
    QPixmap * mPix;
    QPixmap pixFront, pixBack,pixLeft,pixRight;
    int pix_width,pix_height;
    //当前人物位置
    QPoint mCurrentPostion;
    // QGraphicsItem interface
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // PLAYER_H
