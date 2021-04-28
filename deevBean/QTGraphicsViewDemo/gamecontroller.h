#ifndef GAMECONTROLLER_H
#define GAMECONTROLLER_H

//对于一个游戏，通常需要有一个中心控制的类，用于控制所有游戏相关的行为。我们将其取名为GameController。
/**
    GameController的工作是，初始化场景中的游戏对象，开始游戏循环。
    每一个游戏都需要有一个游戏循环，类型于事件循环。
    想象一个每秒滴答 30 次的表。每次响起滴答声，游戏对象才有机会执行相应的动作：
    移动、检查碰撞、攻击或者其它一些游戏相关的活动。
    为方便起见，我们将这一次滴答成为一帧，那么，每秒 30 次滴答，就是每秒 30 帧。
    游戏循环通常使用定时器实现，因为应用程序不仅仅是一个游戏循环，
    还需要响应其它事件，比如游戏者的鼠标键盘操作
    正因为如此，我们不能简单地使用无限的 for 循环作为游戏循环。
    GameController创建并开始游戏循环。当然，我们也可以加入pause()和resume()函数。
*/

/**
 * @brief The GameController class
 * 在 Graphics View Framework 中，每一帧都应该调用一个称为advance()的函数。
 * QGraphicsScene::advance()会调用场景中每一个元素自己的advance()函数。
 * 所以，如果图形元素需要做什么事，必须重写QGraphicsItem的advance()，然后在游戏循环中调用这个函数。
 */
#include <QGraphicsScene>
#include <QObject>
#include <QTimer>
#include <QGraphicsScene>
#include "Snake.h"

#include "food.h"
class GameController:public QObject
{
public:
    GameController(QGraphicsScene *scene, QObject *parent);

    bool eventFilter(QObject *object, QEvent *event) override;
//private:
//    首先开启充当游戏循环的定时器，定时间隔是 1000 / 33 毫秒，也就是每秒 30（1000 / 33 = 30）帧。
    QTimer timer;
//    GameController有两个成员变量：scene 和 snake，我们将第一个食物和蛇都加入到场景中。
//    同时，我们为GameController添加了事件过滤器，以便监听键盘事件 这里我们先不管这个事件过滤器，
    QGraphicsScene *scene;
    Snake *snake;

    void pause();
    void resume();
    void handleKeyPressed(QKeyEvent *event);
    void snakeAteFood(Snake *snake, Food *food);
    void snakeAteItself(Snake *snake);
    void addNewFood();
    void gameOver();
};

#endif // GAMECONTROLLER_H
