#include "SingleGame.h"
#include <QDebug>
#include <QTimer>

SingleGame::SingleGame() {}

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
        Step *step = steps.back();
        steps.removeLast();

        fakeMove(step);
        int   score;
        if(isLost(true)){//：如果红棋（对方）死了，返回最高分
            score= 100000;
            if (ret != nullptr) delete ret;
            ret = step;
            unfakeMove(step);
            qDebug() << "getBestMove isLost true "  ;
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
            case  MyStone::JIANG:{//九宫格内
                if(isBottomSide(i)){
                    startRow=7,endRow=9,startCol=3,endCol=5;
                }else{
                    startRow=0,endRow=2,startCol=3,endCol=5;
                }
                break;
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
    MyWidget::click(id, col, row);
    //电脑执黑,该电脑走了
    if (!bTranRed && m_winner == 0) {
        //todo :机器计算移到线程里
        QTimer::singleShot(100, [=]() {
            Step *step = getBestMove();
            if(step==nullptr){
                iAmLost(false);
            }else{
                //电脑走棋
                //logStep(step->_moveid,step->_killid, step->_colTo, step->_rowTo);
                //记录走棋
                saveStep(step->_moveid, step->_killid, step->_colTo, step->_rowTo, mPassSteps);
                //qDebug()<<"add step  "<<"moveId:"<<step->_moveid<<"killId:"<<step->_killid<<"col:"<<step->_colTo<<"row:"<<step->_rowTo;

                killStone(step->_killid);
                moveStone(step->_moveid, step->_colTo, step->_rowTo);
                mUseTime=0;
                delete step;
            }
            m_winner=judgeGameOver();
            update();
        });
    }
}
