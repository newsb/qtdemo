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
    mPlayer->setZValue(2); // player显示在泡泡前面，泡泡zvalue默认是0
    mScene->addItem(mPlayer);
}

//初始化四周的墙壁
void  GameView::initGameData(){

    for (int r=0;r<ROW;r++) {
        for (int c=0;c<COL;c++) {
            mMap[r][c]=new Cell(SPACE,r,c);
            mScene->addItem( mMap[r][c]);
        }
     }

    //首尾列
    for(int i=0;i<ROW;i++){
//        map[i][0]=WALL;
//        map[i][COL-1]=WALL;

        mMap[i][0]->mAttr= WALL ;
        mMap[i][COL-1]->mAttr= WALL ;
    }
    //首尾行
    for(int i=0;i<COL;i++){
//        map[0][i]=WALL;
//        map[ROW-1][i]=WALL;

        mMap[0][i]->mAttr= WALL ;
        mMap[ROW-1][i]->mAttr= WALL ;
    }
    //随机生成砖块
    for (int r=0;r<ROW;r++) {
        for (int c=0;c<COL;c++) {
//            if(map[r][c]==SPACE){
//                quint32 rand =QRandomGenerator::global()->bounded(3);
////                qDebug()<<"rand=="<<rand;
//                if(rand==2){
//                    map[r][c]= BRICK;
//                }
//            }


            if(mMap[r][c]->mAttr==SPACE){
                quint32 rand =QRandomGenerator::global()->bounded(3);
                if(rand==2){
                    mMap[r][c]->mAttr= BRICK ;
                }
            }
        }
    }

}

void GameView::drawBackground(QPainter *painter, const QRectF &rect)
{
    Q_UNUSED(rect);
    Q_UNUSED(painter);
//    for (int r=0;r<ROW;r++) {
//        for (int c=0;c<COL;c++) {
//            switch (map[r][c]) {
//            case WALL:
//                painter->drawPixmap(rowCol2Coordinate(r,c)
//                                    ,QPixmap(":/res/wall.jpg").scaled(WALL_BRICK_SIZE,WALL_BRICK_SIZE));
//                break;
//            case BRICK:
//                painter->drawPixmap(rowCol2Coordinate(r,c)
//                                    ,QPixmap(":/res/brick.jpg").scaled(WALL_BRICK_SIZE,WALL_BRICK_SIZE));
//                break;
//            case SPACE:
//            case BUBBLE:
//                painter->drawPixmap(rowCol2Coordinate(r,c)
//                                    ,QPixmap(":/res/space.jpg").scaled(WALL_BRICK_SIZE,WALL_BRICK_SIZE));
//                break;
//            default:
//                qDebug()<<"errval :map[r][c]="<<map[r][c];
//                 break;
//            }
//        }
//    }
}

void GameView::keyPressEvent(QKeyEvent *event)
{
    QGraphicsView::keyPressEvent(event);

    bool canWalk=true;
    QPoint pt=mPlayer->mCurrentPostion;

    switch (event->key()) {
    case Qt::Key_Left :
    case Qt::Key_A :{
        mPlayer->mPix=&mPlayer->pixLeft;
        pt.rx()-=Player::STEP_UNIT;

        ATTR attr=attrAt(pt);
        if(attr!=SPACE){
                canWalk= false;
        }
        if(canWalk){
//            mPlayer->walkAStep(Player::LEFT);
            mPlayer->mCurrentPostion.rx()-=Player::STEP_UNIT;
             mPlayer->setPos( mPlayer->mCurrentPostion);
        }else
            mPlayer->update();
        break;
    }
    case Qt::Key_Right:
    case Qt::Key_D:{
        mPlayer->mPix=&mPlayer->pixRight;
        ATTR attr=attrAt(QPoint(pt.x()+WALL_BRICK_SIZE,pt.y()));
        if(attr!=SPACE){
                canWalk= false;
        }
        if(canWalk){
//            mPlayer->walkAStep(Player::RIGHT);
            mPlayer->mCurrentPostion.rx()+=Player::STEP_UNIT;
             mPlayer->setPos( mPlayer->mCurrentPostion);
        }else
            mPlayer->update();
        break;
    }
    case Qt::Key_Up:
    case Qt::Key_W:{
        mPlayer->mPix=&mPlayer->pixBack;
        pt.ry()-=Player::STEP_UNIT;
        ATTR attr=attrAt(pt);
        if(attr!=SPACE){
            canWalk= false;
        }
        if(canWalk){
//            mPlayer->walkAStep(Player::UP);
            mPlayer->mCurrentPostion.ry()-=Player::STEP_UNIT;
             mPlayer->setPos( mPlayer->mCurrentPostion);
        }else
            mPlayer->update();
        break;
    }
    case Qt::Key_Down:
    case Qt::Key_S:{

        mPlayer->mPix=&mPlayer->pixFront;
        ATTR attr=attrAt(QPoint(pt.x(),pt.y()+WALL_BRICK_SIZE));
        if(attr!=SPACE){
                canWalk= false;
        }
        if(canWalk){
//            mPlayer->walkAStep(Player::DOWN);
            mPlayer->mCurrentPostion.ry()+=Player::STEP_UNIT ;
            mPlayer->setPos(mPlayer->mCurrentPostion);
        }else
            mPlayer->update();
        break;
     }

    case Qt::Key_Space:
        //mPlayer->putBubble();

        MyPaoPao *pp=new MyPaoPao();
        QPoint pt =getNearestPoint(mPlayer->mCurrentPostion);
        ATTR attr=attrAt(pt);
        if(attr!=SPACE){
            qDebug()<<"can not put bubble!attr="<<attr;
            return;
        }


        mPaoPaoList.append(pp);
        this-> setBubbleAt(pt);

        pp->setPos(pt);
        pp->setZValue(1);
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


void GameView::setBubbleAt(QPoint pt)
{
    QPoint cAndr= coordinate2RowCol(pt);

    int row=cAndr.y();
    int col=cAndr.x();
//    if (map[row][col]==SPACE){
//        map[row][col]=BUBBLE;
//    }
    if (mMap[row][col]->mAttr==SPACE){
        mMap[row][col]->mAttr=BUBBLE;
    }

}

ATTR GameView::attrAt(int row,int col){
    if(row>=0&&row<=ROW-1&&col>=0&&col<=COL-1){
        return mMap[row][col]->mAttr;
    }
    return UNDEFINE;
}

ATTR GameView::attrAt(QPoint pt)
{
    QPoint cAndr= coordinate2RowCol(pt);

    int row=cAndr.y();
    int col=cAndr.x();
   ATTR attr= attrAt(row,col);
   return attr;
}
