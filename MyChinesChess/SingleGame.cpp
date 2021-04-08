#include "SingleGame.h"
#include <QDebug>
#include <QTimer>

SingleGame::SingleGame() {}

int SingleGame::getMaxScore(int level, int currentMinScore) {
    if (level == 0) return calcScore();

    QVector<Step *> steps;
    getAllPossibleStep(steps);
//    qDebug() << "getMaxScore steps count :" << steps.count();
    int maxScore = -100000;

    while (steps.count()) {
        Step *step = steps.back();
        steps.removeLast();

        fakeMove(step);
        int score = getMinScore(level - 1, maxScore); // calcScore();
        unfakeMove(step);
//#if 0
        if (score >= currentMinScore) {
            //清空steps
            while (steps.count()) {
                Step *step = steps.back();
                steps.removeLast();
                delete step;
            }
            return score;
        }
//#endif
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
    if (level == 0) return calcScore();

    QVector<Step *> steps;
    getAllPossibleStep(steps);
//    qDebug() << "getMinScore steps count :" << steps.count();
    int minScore = 100000;

    while (steps.count()) {
        Step *step = steps.back();
        steps.removeLast();

        fakeMove(step);
        int score = getMaxScore(level - 1, minScore); // calcScore(); //
        unfakeMove(step);

//#if 0
        if (score <= currentMaxScore) {
            //清空steps
            while (steps.count()) {
                Step *step = steps.back();
                steps.removeLast();
                delete step;
            }
            return score;
        }
//#endif
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
        int score = getMinScore(_level, maxScore); // calcScore();
        unfakeMove(step);

        if (score > maxScore) {
            maxScore = score;
//            qDebug() << "getBestMove find better step , Score:" << score<<";_moveid:"
//                <<_s[step->_moveid].getText()
//                <<"fromcol:"<<step->_colFrom<<" fromrow:"<<step->_rowFrom
//                     <<"tocol:"<<step->_colTo<<" torow:"<<step->_rowTo
//                     <<"killid:"<<step->_killid;
            if (ret != nullptr) delete ret;

            ret = step;
        } else {
            delete step;
        }
    }
    return ret;
}

void SingleGame::getAllPossibleStep(QVector<Step *> &steps) {
    int min = 16, max = 32;
    if (bTranRed) {
        min = 0, max = 16;
    }
    for (int i = min; i < max; i++) {
        if (_s[i]._dead) continue;

        for (int row = 0; row <= 9; row++) {
            for (int col = 0; col <= 8; col++) {
                int killId = getStoneIdAt(col, row);

                if (killId != -1) {//
                    if (_s[i]._red == _s[killId]._red) continue;
                }

                if (canMove(i, col, row, killId)) {
                    saveStep(i, killId, col, row, steps);
                }
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
        if (_s[i]._dead) continue;
        redTotalScore += chessScore[_s[i]._type];
    }
    for (int i = 16; i < 32; i++) {
        if (_s[i]._dead) continue;
        blackTotalScore += chessScore[_s[i]._type];
    }
    //黑旗总分-红棋总分
    return blackTotalScore - redTotalScore;
}

void SingleGame::click(int id, int col, int row) {
    MyWidget::click(id, col, row);
    //电脑执黑,该电脑走了
    if (!bTranRed && m_winner == 0) {

        QTimer::singleShot(100, [=]() {
            Step *step = getBestMove();
            //电脑走棋
            //logStep(step->_moveid,step->_killid, step->_colTo, step->_rowTo);
            //记录走棋
            saveStep(step->_moveid, step->_killid, step->_colTo, step->_rowTo, mPassSteps);
            //qDebug()<<"add step  "<<"moveId:"<<step->_moveid<<"killId:"<<step->_killid<<"col:"<<step->_colTo<<"row:"<<step->_rowTo;

            killStone(step->_killid);
            moveStone(step->_moveid, step->_colTo, step->_rowTo);
            delete step;
            judgeGameOver();
            update();
        });
    }
}
