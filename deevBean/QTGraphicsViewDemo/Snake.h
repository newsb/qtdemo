#ifndef SNAKE_H
#define SNAKE_H

#include <QGraphicsItem>
//#include "gamecontroller.h"

#include "constants.h"
#include <QList>
//需要用到 GameController 类，但是GameController已经include了Snake类，不能循环包含
// 解决的办法:第一步只声明对方（class GameController;）
//第二步：使用指针（GameController *controller），
//第三步： 不包含头文件gamecontroller.h，在实现文件中再包含gamecontroller.h，
class GameController;

/**
 * 蛇要更复杂一些。在我们的游戏中，蛇是由黄色的小方块组成，这是最简单的实现方式了。
 * 第一个是蛇的头部，紧接着是它的身体。对此，我们有两个必须面对的困难：

    蛇具有复杂得多的形状。 因为蛇的形状随着游戏者的控制而不同，
    因此，我们必须找出一个能够恰好包含蛇头和所有身体块的矩形。
    这也是 boundingRect() 函数所要解决的问题。

    蛇会长大（比如吃了食物之后）。
    因此，我们需要在蛇对象中增加一个用于代表蛇身体长度的growing变量：
    当growing为正数时，蛇的身体增加一格；当growing为负数时，蛇的身体减少一格。

    advance()函数用于编码移动部分，这个函数会在一秒内调用 30 次（这是我们在GameController的定时器中决定的）。
 */

class Snake : public QGraphicsItem
{
public:
//    元素的坐标
    Snake( GameController *c);

    QRectF boundingRect() const override;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) override;

    QPainterPath shape() const override;
//private:
    int GD_Type;
    int growing ;
    int speed;
    QPointF head;
    QList<QPointF> tail;
    int tickCounter  ;
    GameController *controller;

    void moveLeft();
    void moveRight();
    void moveUp();
    void moveDown();
    void handleCollisions();


    enum MoveDirection{MoveLeft,MoveRight,MoveUp,MoveDown,NoMove};
    MoveDirection moveDirection;
    void setMoveDirection(MoveDirection direction);

    // QGraphicsItem interface
public:
    virtual void advance(int phase) override;
};

#endif // FOOD_H
