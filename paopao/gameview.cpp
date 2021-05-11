#include "gameview.h"
#include <QDebug>
#include "mypaopao.h"
#include <QKeyEvent>
#include <QPropertyAnimation>
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
    mPlayer->setZValue(1); // player显示在泡泡前面，泡泡zvalue默认是0
    mScene->addItem(mPlayer);
}

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
            case BUBBLE:
                painter->drawPixmap(rowCol2Coordinate(r,c)
                                    ,QPixmap(":/res/space.jpg").scaled(WALL_BRICK_SIZE,WALL_BRICK_SIZE));
                break;
            default:
//                qDebug()<<"errval :map[r][c]="<<map[r][c];
                 break;
            }
        }
    }
}

void GameView::keyPressEvent(QKeyEvent *event)
{
    QGraphicsView::keyPressEvent(event);
    switch (event->key()) {
        case Qt::Key_Left :
        case Qt::Key_A :
            mPlayer->walkAStep(Player::LEFT);
            break;
        case Qt::Key_Right:
        case Qt::Key_D:
            mPlayer->walkAStep(Player::RIGHT);
            break;
        case Qt::Key_Up:
        case Qt::Key_W:
            mPlayer->walkAStep(Player::UP);
            break;
        case Qt::Key_Down:
        case Qt::Key_S:
            mPlayer->walkAStep(Player::DOWN);
            break;
        case Qt::Key_Space:
            //mPlayer->putBubble();

            MyPaoPao *pp=new MyPaoPao();
            QPoint pt =getNearestPoint(mPlayer->mCurrentPostion);
            ATTR attr=attrAt(pt);
             if(attr!=SPACE){
                qDebug()<<"can not put bubble!attr="<<attr;
                return;
             }

//             bool bubbleExisted=false;
//             for(int i=0;i<mPaoPaoList.count();i++){
//                 if(mPaoPaoList.at(i)->x()==pt.x()&&mPaoPaoList.at(i)->y()==pt.y()){
//                    bubbleExisted=true;
//                    break;
//                 }
//             }
//            if(bubbleExisted){
//                qDebug()<<"can not put bubble!bubbleExisted="<<bubbleExisted;
//                return;
//            }

             mPaoPaoList.append(pp);
                setBubbleAt(pt);

                pp->setPos(pt);
                mScene->addItem(pp);

                QPropertyAnimation *animation=new QPropertyAnimation(pp, "scale",this);
                  animation->setDuration(2000);
    //              timer->setFrameRange(0, 100);//frameChanged()发出的值在0-100之间
    //              timer->setCurveShape(QTimeLine::SineCurve);

                  animation->setStartValue(qreal(1));

                  animation->setKeyValueAt(0.25,0.75);
                  animation->setKeyValueAt(0.5,0.5);
                  animation->setKeyValueAt(0.75,0.75);

                  animation->setEndValue(qreal(1));
                  animation->setLoopCount(-1);
                  animation->setEasingCurve(QEasingCurve::InOutCubic);
                  animation->start();


            break;
    }

}
