#include "gameview.h"
#include <QDebug>

GameView::GameView(QWidget *parent) : QGraphicsView(parent)
      ,mScene(new QGraphicsScene(this))
{
    setFixedSize(1080, 600);
    setWindowTitle("简单");
    mScene->setSceneRect(0, 0, width() - 4, height() - 4);
//    mScene->setSceneRect(-WIN_WIDTH / 2, -WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT);

    this->setScene(mScene);
    initGameData();
    mPlayer=new Player;
    mScene->addItem(mPlayer);
}

#include "global.h"
//初始化四周的墙壁
void  GameView::initGameData(){

    //首尾列
    for(int i=0;i<ROW;i++){
        map[i][0]=WALL;
        map[i][COL-1]=WALL;
    }
    //首尾行
    for(int i=0;i<COL;i++){
        map[0][i]=WALL;
        map[ROW-1][i]=WALL;
    }
    //随机生成砖块
    for (int r=0;r<ROW;r++) {
        for (int c=0;c<COL;c++) {
            if(map[r][c]==SPACE){
                quint32 rand =QRandomGenerator::global()->bounded(3);
//                qDebug()<<"rand=="<<rand;
                if(rand==2){
                    map[r][c]= BRICK;
                }
            }
        }
    }
}

void GameView::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);
    for (int r=0;r<ROW;r++) {
        for (int c=0;c<COL;c++) {
            switch (map[r][c]) {
            case WALL:
                painter->drawPixmap(rowCol2Coordinate(r,c)
                                    ,QPixmap(":/res/wall.jpg").scaled(WALL_BRICK_SIZE,WALL_BRICK_SIZE));
                break;
            case BRICK:
                painter->drawPixmap(rowCol2Coordinate(r,c)
                                    ,QPixmap(":/res/brick.jpg").scaled(WALL_BRICK_SIZE,WALL_BRICK_SIZE));
                break;
            case SPACE:
                painter->drawPixmap(rowCol2Coordinate(r,c)
                                    ,QPixmap(":/res/space.jpg").scaled(WALL_BRICK_SIZE,WALL_BRICK_SIZE));
                break;
            default:
                qDebug()<<"errval :map[r][c]="<<map[r][c];
            }
        }
    }
}

#include <QKeyEvent>
void GameView::keyPressEvent(QKeyEvent *event)
{
    QGraphicsView::keyPressEvent(event);
    switch (event->key()) {
        case Qt::Key_Left:
            mPlayer->walkAStep(Player::LEFT);
            break;
        case Qt::Key_Right:
            mPlayer->walkAStep(Player::RIGHT);
            break;
        case Qt::Key_Up:
            mPlayer->walkAStep(Player::UP);
            break;
        case Qt::Key_Down:
            mPlayer->walkAStep(Player::DOWN);
            break;
        case Qt::Key_Space:
            mPlayer->putBubble();
            break;
    }

}
