#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>

#define WIN_HEIGHT 600
#define WIN_WIDTH 1080
#define WALL_BRICK_SIZE 40
#define ROW (WIN_HEIGHT/WALL_BRICK_SIZE)
#define COL (WIN_WIDTH/WALL_BRICK_SIZE)



class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = nullptr);

signals:

private:
    enum ATTR{
        SPACE,//空白
        WALL,//墙壁（不能炸）、
        BRICK//砖块(可炸）
    };
    //地图map
    int map[ROW][COL]={};//全局变量初始化为0，（SPACE）  //类的成员不会初始化为0,必须手动赋值
    void initData();

    QGraphicsScene *mScene;


protected:
    virtual void drawBackground(QPainter *painter, const QRectF &rect) override;
};

#endif // GAMEVIEW_H
