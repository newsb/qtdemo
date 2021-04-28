#include "mymainwindow.h"

#include <QTimer>
#include "constants.h"
MyMainWindow::MyMainWindow(QWidget *parent) : QMainWindow(parent)
      ,scene(new QGraphicsScene(this))
      ,view(new QGraphicsView(scene,this))
      ,game(new GameController(scene, this))
{
//    setWindowTitle(QDir::currentPath());//exe完整路径

    setCentralWidget(view);
    resize(600, 600);

    initScene();
    initSceneBackground();
    // 在下一次事件循环开始时，立刻 调用this->adjustViewSize()
    //    我们需要在视图绘制完毕后才去改变大小（视图绘制当然是在paintEvent()事件中），因此我们需要在下一次事件循环中调用adjustViewSize()函数。
//    QTimer::singleShot(0, this, SLOT(adjustViewSize()));
    QTimer::singleShot(0, this,  &MyMainWindow::adjustViewSize);
}

void MyMainWindow::adjustViewSize()
{

}

void MyMainWindow::initScene()
{   //默认情况下，场景是无限大的
    scene->setSceneRect(-100, -100, 200, 200);
    /*Graphics View Framework 为每一个元素维护三个不同的坐标系：
        场景坐标，
        元素自己的坐标
        以及其相对于父组件的坐标。
    除了元素在场景中的位置，其它几乎所有位置都是相对于元素坐标系的。
    */
}

void MyMainWindow::initSceneBackground()
{
    //创建一个边长TILE_SIZE的QPixmap
    QPixmap bg(TILE_SIZE, TILE_SIZE);
    //其使用灰色填充矩形。我们没有设置边框颜色，默认就是黑色。
    QPainter p(&bg);
    //然后将这个QPixmap作为背景画刷，铺满整个视图。
    p.setBrush(QBrush(Qt::gray));
    p.drawRect(0, 0, TILE_SIZE, TILE_SIZE);



    view->setBackgroundBrush(QBrush(bg));
}


void MyMainWindow::paintEvent(QPaintEvent *event)
{
}
