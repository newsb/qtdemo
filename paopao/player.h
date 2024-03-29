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
//    bool walkAStep(Direction direct);
//    void putBubble();
    static const int STEP_UNIT=20;
    QPixmap * mPix;
    QPixmap pixFront, pixBack,pixLeft,pixRight;

signals:
private:
    int pix_width,pix_height;
public:
    //当前人物位置
    QPoint mCurrentPostion;
public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;
};

#endif // PLAYER_H
