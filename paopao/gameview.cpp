#include "gameview.h"
#include <QDebug>
#include <QRandomGenerator>
GameView::GameView(QWidget *parent) : QGraphicsView(parent)
      ,mScene(new QGraphicsScene(this))
{
    setFixedSize(1080, 600);
    setWindowTitle("简单");
    mScene->setSceneRect(0, 0, width() - 4, height() - 4);
//    mScene->setSceneRect(-WIN_WIDTH / 2, -WIN_HEIGHT / 2, WIN_WIDTH, WIN_HEIGHT);

    this->setScene(mScene);
    initData();
}


//初始化四周的墙壁
//随机生成砖块
void GameView::initData(){

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
    //中间的墙
    for (int r=0;r<ROW;r++) {
        for (int c=0;c<COL;c++) {
            if(map[r][c]!=WALL){
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
                painter->drawPixmap(c*WALL_BRICK_SIZE,r*WALL_BRICK_SIZE
                                    ,QPixmap(":/res/wall.jpg").scaled(WALL_BRICK_SIZE,WALL_BRICK_SIZE));
                break;
            case BRICK:
                painter->drawPixmap(c*WALL_BRICK_SIZE,r*WALL_BRICK_SIZE
                                    ,QPixmap(":/res/brick.jpg").scaled(WALL_BRICK_SIZE,WALL_BRICK_SIZE));
                break;
            case SPACE:
                painter->drawPixmap(c*WALL_BRICK_SIZE,r*WALL_BRICK_SIZE
                                    ,QPixmap(":/res/space.jpg").scaled(WALL_BRICK_SIZE,WALL_BRICK_SIZE));
                break;
            default:
                qDebug()<<"errval :map[r][c]="<<map[r][c];
            }
        }
    }
}
