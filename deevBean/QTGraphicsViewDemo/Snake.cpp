#include "Snake.h"

#include <QPainter>
#include "food.h"
#include "gamecontroller.h"

static const qreal SNAKE_SIZE = TILE_SIZE;

Snake::Snake(GameController *c):
      head(0, 0),
      growing(7),
      speed(5),
      moveDirection(NoMove),
      controller(c)
{
//    setPos(x, y);
    setData(GD_Type, GO_Snake);
}
//这个函数的算法是：遍历蛇身体的每一个方块，
//找出所有部分的最大的 x 坐标和 y 坐标，以及最小的 x 坐标和 y 坐标。这样，夹在其中的便是蛇身体的外围区域。
QRectF Snake::boundingRect() const
{
    qreal minX = head.x();
    qreal minY = head.y();
    qreal maxX = head.x();
    qreal maxY = head.y();

    foreach (QPointF p, tail) {
        maxX = p.x() > maxX ? p.x() : maxX;
        maxY = p.y() > maxY ? p.y() : maxY;
        minX = p.x() < minX ? p.x() : minX;
        minY = p.y() < minY ? p.y() : minY;
    }

    QPointF tl = mapFromScene(QPointF(minX, minY));
    QPointF br = mapFromScene(QPointF(maxX, maxY));

    QRectF bound = QRectF(tl.x(),  // x
              tl.y(),  // y
              br.x() - tl.x() + SNAKE_SIZE,      // width
              br.y() - tl.y() + SNAKE_SIZE       //height
     );

    return bound;
}
//shape()函数决定了蛇身体的形状，我们遍历蛇身体的每一个方块向路径中添加：
QPainterPath Snake::shape() const
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);

    path.addRect(QRectF(0, 0, SNAKE_SIZE, SNAKE_SIZE));

    foreach (QPointF p, tail) {
        QPointF itemp = mapFromScene(p);
        path.addRect(QRectF(itemp.x(), itemp.y(), SNAKE_SIZE, SNAKE_SIZE));
    }

    return path;
}
void Snake::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *)
{
    painter->save();
    painter->fillPath(shape(), Qt::yellow);
    painter->restore();
}

void Snake::setMoveDirection(Snake::MoveDirection direction)
{
    if (moveDirection == MoveLeft && direction == MoveRight)
        return;
    if (moveDirection == MoveRight && direction == MoveLeft)
        return;
    if (moveDirection == MoveUp && direction == MoveDown)
        return;
    if (moveDirection == MoveDown && direction == MoveUp)
        return;
    moveDirection=direction;
}

//QGraphicsItem::advance()函数接受一个 int 作为参数。这个 int 代表该函数被调用的时间。
void Snake::advance(int step)
{
    //QGraphicsItem::advance()函数会被QGraphicsScene::advance()函数调用两次：
    //第一次时这个 int 为 0，代表即将开始调用；第二次这个 int 为 1，代表已经开始调用。
    //在我们的代码中，我们只使用不为 0 的阶段，因此当 !step 时，函数直接返回。
    if (!step) {
        return;
    }
    //tickCounter实际是我们内部的一个计时器。
    //我们使用 speed 作为蛇的两次动作的间隔时间，直接影响到游戏的难度。
    //speed 值越大，两次运动的间隔时间越大，游戏越简单。
    //这是因为随着 speed 的增大，tickCounter % speed != 0 的次数响应越多，刷新的次数就会越少，蛇运动得越慢。
    if (tickCounter++ % speed != 0) {
        return;
    }
    if (moveDirection == NoMove) {
        return;
    }
    /**
    growing是正在增长的方格数。当其大于 0 时，我们将头部追加到尾部的位置，同时减少一个方格；
    当其小于 0 时，我们删除第一个，然后把头部添加进去。我们可以把 growing 看做即将发生的变化。
    比如，我们将 growing 初始化为 7。第一次运行advance()时，由于 7 > 1，因此将头部追加，然后 growing 减少 1。
    直到 growing 为 0，此时，蛇的长度不再发生变化，直到我们吃了一个食物。
    */
    //    if(tail.isEmpty())return;
    if (growing > 0) {
        QPointF tailPoint = head;
        tail << tailPoint;
        growing -= 1;
    } else {
        tail.takeFirst();
        tail << head;
    }

    switch (moveDirection) {
    case MoveLeft:
        moveLeft();
        break;
    case MoveRight:
        moveRight();
        break;
    case MoveUp:
        moveUp();
        break;
    case MoveDown:
        moveDown();
        break;
    default:
        break;
    }

    setPos(head);
    handleCollisions();
}
/**
 * 四个以 move 开头的函数，内容都很类似：
 * 分别以 SNAKE_SIZE 为基准改变头部坐标，然后与场景边界比较，大于边界值时，设置为边界值。
 * 这么做的结果是，当蛇运动到场景最右侧时，会从最左侧出来；当运行到场景最上侧时，会从最下侧出来。
 */
void Snake::moveLeft(){
    head.rx() -= SNAKE_SIZE;
    if (head.rx() < -100) {
        head.rx() = 100;
    }
}

void Snake::moveRight(){
    head.rx() += SNAKE_SIZE;
    if (head.rx() > 100) {
        head.rx() = -100;
    }
}

void Snake::moveUp(){
    head.ry() -= SNAKE_SIZE;
    if (head.ry() < -100) {
        head.ry() = 100;
    }
}

void Snake::moveDown(){
    head.ry() += SNAKE_SIZE;
    if (head.ry() > 100) {
        head.ry() = -100;
    }
}

void Snake::handleCollisions(){
    QList<QGraphicsItem *> collisions = collidingItems();

    // Check collisions with other objects on screen
    foreach (QGraphicsItem *collidingItem, collisions) {
        if (collidingItem->data(GD_Type) == GO_Food) {
            // Let GameController handle the event by putting another apple
            controller->snakeAteFood(this, (Food *)collidingItem);
            growing += 1;
        }
    }

    // Check snake eating itself
    if (tail.contains(head)) {
        controller->snakeAteItself(this);
    }
}


