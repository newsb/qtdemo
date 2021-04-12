#include "SingleGame.h"
#include <QDebug>
#include <QTimer>
#include <QtConcurrent>
#include <QCloseEvent>

SingleGame::SingleGame(QWidget *parent)
    : MyWidget(parent) {

    connect(this,&SingleGame::computerMoveFinished,this,&SingleGame::updateComputerMove,Qt::QueuedConnection);

}

SingleGame::~SingleGame(){

}

int SingleGame::getMaxScore(int level, int currentMinScore) {
    if (level == 0) return calcScore( );

    if(isLost(false)){//：如果黑棋（机器自己）死了，返回最低分
        return -100000;
        qDebug() << "getMaxScore isLost false "  ;
    }else if(isLost(true)){//：如果红棋（对方）死了，返回最高分
        return 100000;
        qDebug() << "getMaxScore isLost true "  ;
    }

    QVector<Step *> steps;
    getAllPossibleStep(steps);
//    qDebug() << "getMaxScore steps count :" << steps.count();
    int maxScore = -100000;

    while (steps.count()) {
        if( mStopping) return 0;
        Step *step = steps.back();
        steps.removeLast();

        fakeMove(step);
        int   score;

          score = getMinScore(level - 1, maxScore);

        unfakeMove(step);
#if 1
        if (score >= currentMinScore) {
            //清空steps
            while (steps.count()) {
                Step *step = steps.back();
                steps.removeLast();
                delete step;
            }
            return score;
        }
#endif
        if (score > maxScore) {
            maxScore = score;
//            qDebug() << "getMaxScore find better step , Score:" << score<<";_moveid:"
//                     <<_s[step->_moveid].getText()
//                     <<"fromcol:"<<step->_colFrom<<" fromrow:"<<step->_rowFrom
//                     <<"tocol:"<<step->_colTo<<" torow:"<<step->_rowTo
//                     <<"killid:"<<step->_killid;
        }
        delete step;
    }
    return maxScore;
}

int SingleGame::getMinScore(int level, int currentMaxScore) {
    if (level == 0) return calcScore( );
    if(isLost(false)){//：如果黑棋（对方、机器）死了，返回最高分
        return 100000;
        qDebug() << "getMinScore isLost false "  ;
    }else if(isLost(true)){//：如果红棋（自己）死了，返回最低分
        return -100000;
        qDebug() << "getMinScore isLost true "  ;
    }

    QVector<Step *> steps;
    getAllPossibleStep(steps);
//    qDebug() << "getMinScore steps count :" << steps.count();
    int minScore = 100000;

    while (steps.count()) {
        if( mStopping) return 0;
        Step *step = steps.back();
        steps.removeLast();

        fakeMove(step);
        int   score  = getMaxScore(level - 1, minScore);

        unfakeMove(step);

#if 1
        if (score <= currentMaxScore) {
            //清空steps
            while (steps.count()) {
                Step *step = steps.back();
                steps.removeLast();
                delete step;
            }
            return score;
        }
#endif
        if (score < minScore) {
            minScore = score;
//            qDebug() << "getMinScore find better step , Score:" << score<<";_moveid:"
//                     <<_s[step->_moveid].getText()
//                     <<"fromcol:"<<step->_colFrom<<" fromrow:"<<step->_rowFrom
//                     <<"tocol:"<<step->_colTo<<" torow:"<<step->_rowTo
//                     <<"killid:"<<step->_killid;
        }
        delete step;
    }
    //    qDebug() << "oppnent worse step , Score:" << minScore;
    return minScore;
}

Step *SingleGame::getBestMove() {
    // 1获取所有可以走的步
    QVector<Step *> steps;
    getAllPossibleStep(steps);

    qDebug() << "getBestMove steps count :" << steps.count();
    // 2试着走一下
    // 3.评估分数，获取最高分
    int maxScore = -100000;
    Step *ret = nullptr;
    while (steps.count()) {
        if( mStopping) return ret;

        Step *step = steps.back();
        steps.removeLast();

        fakeMove(step);
        int   score;
        if(isLost(true)){//：如果红棋（对方）死了，返回最高分
            score= 100000;
            if (ret != nullptr) delete ret;
            ret = step;
            unfakeMove(step);
            qDebug() << "getBestMove isLost========== true "  ;
        }else{
            score = getMinScore(_level, maxScore);
            if (score > maxScore) {
                maxScore = score;
                qDebug() << "getBestMove find better step , Score:" << score<<";_moveid:"
                         <<_s[step->_moveid].getText()
                         <<"fromcol:"<<step->_colFrom<<" fromrow:"<<step->_rowFrom
                         <<"tocol:"<<step->_colTo<<" torow:"<<step->_rowTo
                         <<"killid:"<<step->_killid;
                if (ret != nullptr) delete ret;

                ret = step;
            } else {
                delete step;
            }
            unfakeMove(step);
        }


    }
    return ret;
}

void SingleGame::getAPossibleStep(int stoneId,int col,int row,QVector<Step *> &steps){

    int killId = getStoneIdAt(col, row);
    if (killId != -1&&_s[stoneId]._red == _s[killId]._red) {

    }else{
        if (canMove(stoneId, col, row, killId)) {
            saveStep(stoneId, killId, col, row, steps);
        }
    }
}
void SingleGame::getAllPossibleStep(QVector<Step *> &steps) {
    int min = 16, max = 32;
    if (bTranRed) {
        min = 0, max = 16;
    }
    for (int i = min; i < max; i++) {
        if (_s[i]._dead) continue;

        int startRow=0,endRow=9,startCol=0,endCol=8;
        switch (_s[i]._type) {
            case MyStone::BING:{//兵、只检查前后左右4个位置
                startRow=_s[i]._row-1,endRow=_s[i]._row+1,startCol=_s[i]._col-1,endCol=_s[i]._col+1;
                break;
            }
            case  MyStone::CHE:
            case  MyStone::PAO:{//炮、只检查2直线上的位置
                startRow=_s[i]._row,endRow=_s[i]._row,startCol=0,endCol=8;
                for (int row = startRow; row <= endRow; row++) {
                    for (int col = startCol; col <= endCol; col++) {
                        getAPossibleStep(i,col,row,steps);
                    }
                }
                startRow=0,endRow=9,startCol=_s[i]._col,endCol=_s[i]._col;
                break;
            }
            case  MyStone::MA:{//
                break;
            }
            case  MyStone::XIANG:{//
                startRow=-1,endRow=-1,startCol=-1,endCol=-1;
                if(isBottomSide(i)){
                    // [[0,2] [0,6] ,[2,0],[2,4] [2,8] ,[4,2],4-6]
                    // [9,2] [9,6] [7,0],[7,4] [7,8] ,  5,2  ,5-6
                    static int  XIANG_POS[14][2]={{0,2},{0,6},{2,0},{2,4},{2,8},{4,2},{4,6},
                                           {9,2},{9,6},{7,0},{7,4},{7,8},{5,2},{5-6} };
                    for (int c=0;c<14;c++) {
                       getAPossibleStep(i, XIANG_POS[c][1],XIANG_POS[c][0],steps);
                    }
                }
                break;
            }
            case  MyStone::SHI:
            case  MyStone::JIANG:{
                //将要检查是否可以直接干死对方的老将
//                startRow=_s[i]._row,endRow=_s[i]._row,startCol=0,endCol=8;

//                for (int row = startRow; row <= endRow; row++) {
//                    for (int col = startCol; col <= endCol; col++) {
//                        getAPossibleStep(i,col,row,steps);
//                    }
//                }
//                //九宫格内,!!
//                if(isBottomSide(i)){
//                    startRow=7,endRow=9,startCol=3,endCol=5;
//                }else{
//                    startRow=0,endRow=2,startCol=3,endCol=5;
//                }
//                break;
            }
        }

        for (int row = startRow; row <= endRow; row++) {
            for (int col = startCol; col <= endCol; col++) {
                getAPossibleStep(i,col,row,steps);
            }
        }
    }
}



void SingleGame::fakeMove(Step *step) {
    killStone(step->_killid);
    moveStone(step->_moveid, step->_colTo, step->_rowTo);
}

int SingleGame::calcScore() {

    //    enum TYPE         { CHE, MA, XIANG, SHI, JIANG, BING, PAO };
    static int chessScore[] = {100, 50, 20, 20, 1550, 10, 50};
    int redTotalScore = 0, blackTotalScore = 0;

    for (int i = 0; i < 16; i++) {
        if (_s[i]._dead){
//            //该黑棋走的时候
//            if (isMyself){
//                //如果红棋（对方）的将死了，分数返回最高
//                if (_s[i]._type==MyStone::JIANG){
//                    return 100000;
//                }
//            }else{//该红棋走的时候
//                //如果红棋（己方）的将死了，分数返回最低
//                if (_s[i]._type==MyStone::JIANG){
//                    return -100000;
//                }
//            }
            continue;
        }
        redTotalScore += chessScore[_s[i]._type];
    }
    for (int i = 16; i < 32; i++) {

        if (_s[i]._dead){
//            //该黑棋走的时候
//            if (isMyself){
//                //如果自己（黑旗）的将死了，分数返回最低
//                if (_s[i]._type==MyStone::JIANG){
//                    return -100000;
//                }
//            }else{//该红棋走的时候
//                //如果对方（黑旗）的将死了，分数返回最高
//                if (_s[i]._type==MyStone::JIANG){
//                    return 100000;
//                }
//            }
            continue;
        }
        blackTotalScore += chessScore[_s[i]._type];
    }
    //黑旗总分-红棋总分
    return blackTotalScore - redTotalScore;
}

void SingleGame::click(int id, int col, int row) {
    if  (isComputerMoving){
        return;
    }

    MyWidget::click(id, col, row);
    //电脑执黑,该电脑走了
    if (!bTranRed && m_winner == 0) {
        //等人走的棋子刷新
        QTimer::singleShot(100, [=]() {
            startComputerMove();

#if 0
            Step *step = getBestMove();
            updateComputerMove(step);
#endif
        });
    }
}

QPointF SingleGame::center(int id) {

    if (isComputerMoving){
        return QPointF(PADDING_LEFT + (_ss[id]._col + 1) * mColumnWidth, PADDING_TOP + (_ss[id]._row + 1) * mRowHeight);
    }else{
        return MyWidget::center(id);
    }
}

void SingleGame::closeEvent(QCloseEvent *event)
{
    /* 等待任何悬垂的线*/
    mStopping=true;
   if (QThreadPool::globalInstance()->activeThreadCount())
       QThreadPool::globalInstance()->waitForDone();
   event->accept();
}

void SingleGame::drawStone(QPainter &painter, int id)
{
    if (isComputerMoving){

        if (_ss[id]._dead) return;
        painter.save();
        QPointF c = center(id);
        QRect rect = QRect(c.x() - _r, c.y() - _r, 2 * _r, 2 * _r);
        if (selectId == id) {
            painter.setBrush(QBrush(Qt::white));
        } else {
            painter.setBrush(QBrush(Qt::lightGray));
        }

        painter.setPen(Qt::darkYellow);
        painter.drawEllipse(c, _r + 5, _r + 5);

        painter.setPen(Qt::darkYellow);
        painter.drawEllipse(c, _r, _r);

        painter.setPen(Qt::black);
        if (_ss[id]._red) {
            painter.setPen(Qt::red);
        }
        painter.setFont(QFont("微软雅黑", _r, 700));
        painter.drawText(rect, _ss[id].getText(), QTextOption(Qt::AlignCenter));

        painter.restore();
    }else{
        MyWidget::drawStone(painter,id);
    }
}

void SingleGame::startComputerMove( ){
    for (int i=0;i<32;i++) {
//        if(!_s[i]._dead){
            _ss[i]. _col=_s[i]._col;
            _ss[i]._row=_s[i]. _row;
            _ss[i]._dead=_s[i]. _dead;
            _ss[i]._red=_s[i]. _red;
            _ss[i]._type=_s[i]. _type;
            _ss[i]._id=_s[i]. _id;
//        }
    }
    qDebug()<<"start comput " ;
    QtConcurrent::run([=](){
//        multex.lock();
        isComputerMoving=true;
//        multex.unlock();
        Step *step= getBestMove();
//        multex.lock();
        isComputerMoving=false;
//        multex.unlock();
        qDebug()<<"QtConcurrent---------> step  "<<"moveId:"<<step->_moveid<<"killId:"<<step->_killid
               <<"col:"<<step->_colTo<<"row:"<<step->_rowTo;
        //主线程里调用槽函数
//            QMetaObject::invokeMethod(this,"updateComputerMove", Qt::QueuedConnection,Q_ARG(Step *, step) );
        if(!mStopping)
            emit computerMoveFinished(step);
    });
}

void SingleGame::updateComputerMove(Step *step){
    //如果是正在关闭，则不再刷新
    if(mStopping) return;
    //如果没有可走的步数，就认输
    if(step==nullptr){
        //认输
        iAmLost(false);
    }else{
        int i=step->_moveid;
        if(step->_killid>=0&&step->_killid<32){
            _ss[i]. _col=_s[i]._col;
            _ss[i]._row=_s[i]. _row;
        }
        if(step->_killid>=0&&step->_killid<32){
            _ss[step->_killid]._dead=_s[step->_killid]. _dead;
        }


        qDebug()<<"updateComputerMove---------> step  "<<"moveId:"<<step->_moveid<<"killId:"<<step->_killid
               <<"col:"<<step->_colTo<<"row:"<<step->_rowTo;
        //电脑走棋
        //logStep(step->_moveid,step->_killid, step->_colTo, step->_rowTo);
        //记录走棋
        saveStep(step->_moveid, step->_killid, step->_colTo, step->_rowTo, mPassSteps);
        //qDebug()<<"add step  "<<"moveId:"<<step->_moveid<<"killId:"<<step->_killid<<"col:"<<step->_colTo<<"row:"<<step->_rowTo;

        killStone(step->_killid);
        moveStone(step->_moveid, step->_colTo, step->_rowTo);
        mUseTime=0;
        if(isBottomSide(step->_moveid)){
            mLastSelectIdRed=step->_moveid;
        }else{
            mLastSelectIdBlack=step->_moveid;
        }
        delete step;
    }
    m_winner=judgeGameOver();
    update();
    bells->play();
}
