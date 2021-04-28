#include "gamecontroller.h"
#include <QEvent>
#include <QKeyEvent>
#include <QTimer>
GameController::GameController(QGraphicsScene *scene, QObject *parent) :
      QObject(parent),
      scene(scene)
      ,snake(new Snake(this))
{
    timer.start(1000/33);

    Food *a1 = new Food(0, -50);
    scene->addItem(a1);
    scene->addItem(snake);
    scene->installEventFilter(this);
   resume();
}

void GameController::snakeAteFood(Snake *snake, Food *food)
{
    Q_UNUSED(snake);

    scene->removeItem(food);
    delete food;

    addNewFood();
}
/*
如果蛇咬到了它自己，游戏即宣告结束。
因此，我们直接调用gameOver()函数。
这个函数将场景清空，然后重新创建蛇并增加第一个食物。
为什么我们不直接调用gameOver()函数，而是利用QTimer调用呢（希望你没有忘记QTimer::singleShot(0, ...)的用法）？
这是因为，我们不应该在一个 update 操作中去清空整个场景。因此我们使用QTimer，在 update 事件之后完成这个操作。
*/
void GameController::snakeAteItself(Snake *snake)
{
    Q_UNUSED(snake);
    QTimer::singleShot(0, this, &GameController::gameOver  );
}
/**
 * 将游戏场景继承QGraphcisScene当然满足这个关系，无可厚非。但是，继承还有一个“特化”的含义，我们只想控制键盘事件，
 * 并没有添加其它额外的代码，因此感觉并不应该作此继承。
 * 第二，我们希望将表示层与控制层分离：明明已经有了GameController，
 * 显然，这是一个用于控制游戏的类，那么，为什么键盘控制还要放在场景中呢？
 * 这岂不将控制与表现层耦合起来了吗？基于以上两点考虑，我们选择不继承QGraphicsScene，
 * 而是在GameController中为场景添加事件过滤器，从而完成键盘事件的处理。
 *
 * 这段代码并不复杂：只是设置蛇的运动方向。记得我们在前面的代码中，已经为蛇添加了运动方向的控制，
 * 因此，我们只需要修改这个状态，即可完成对蛇的控制。由于前面我们已经在蛇的对象中完成了相应控制的代码，因此这里的游戏控制就是这么简单。
 */
void GameController::handleKeyPressed(QKeyEvent *event){
    switch (event->key()) {
    case Qt::Key_Left:
        snake->setMoveDirection(Snake::MoveLeft);
        break;
    case Qt::Key_Right:
        snake->setMoveDirection(Snake::MoveRight);
        break;
    case Qt::Key_Up:
        snake->setMoveDirection(Snake::MoveUp);
        break;
    case Qt::Key_Down:
        snake->setMoveDirection(Snake::MoveDown);
        break;
    }
}
/*
在addNewFood()代码中，我们首先计算新的食物的坐标：使用一个循环，直到找到一个不在蛇身体中的坐标。
为了判断一个坐标是不是位于蛇的身体上，我们利用蛇的shape()函数。需要注意的是，shape()返回元素坐标系中的坐标，
而我们计算而得的 x，y 坐标位于场景坐标系，因此我们必须利用QGraphicsItem::mapFromScene()将场景坐标系映射为元素坐标系。
当我们计算出食物坐标后，我们在堆上重新创建这个食物，并将其添加到游戏场景。
*/
void GameController::addNewFood()
{
    int x, y;

    do {
        x = (int) (qrand() % 200) / 10;
        y = (int) (qrand() % 200) / 10;

        x *= 10;
        y *= 10;
    } while (snake->shape().contains(snake->mapFromScene(QPointF(x + 5, y + 5))));

    Food *food = new Food(x , y);
    scene->addItem(food);
}


void GameController::gameOver()
{
    scene->clear();
    snake = new Snake(this);
    scene->addItem(snake);
    addNewFood();
}
//只是连接或者断开定时器的信号。
void GameController::pause()
{
    disconnect(&timer,&QTimer::timeout,scene,&QGraphicsScene::advance);
    //    isPause = true;
}

void GameController::resume()
{
    connect(&timer, &QTimer::timeout,scene,&QGraphicsScene::advance);
    //    isPause = false;
}
/**
 * 我们使用QGraphicsScene作为游戏场景。为什么不直接继承QGprahicsScene，重写其keyPressEvent()函数呢？
 * 这里的考虑是：第一，我们不想只为重写一个键盘事件而继承QGraphicScene。这不符合面向对象设计的要求。继承首先应该有“是一个（is-a）”的关系。
 *
 */
bool GameController::eventFilter(QObject *object, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        handleKeyPressed((QKeyEvent *)event);
        return true;
    } else {
        return QObject::eventFilter(object, event);
    }
}


