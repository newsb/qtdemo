#include "SingleGame.h"
#include <QDebug>
#include <QTimer>

SingleGame::SingleGame() {}

int SingleGame::getMaxScore(int level, int currentMinScore) {
    if (level == 0) return calcScore();

    QVector<Step *> steps;
    getAllPossibleStep(steps);
    int maxScore = -100000;

    while (steps.count()) {
        Step *step = steps.back();
        steps.removeLast();

        fakeMove(step);
        int score = getMinScore(level - 1, maxScore); // calcScore();
        unfakeMove(step);

        delete step;
        if (score >= currentMinScore) {
            //清空steps
            while (steps.count()) {
                Step *step = steps.back();
                steps.removeLast();
                delete step;
            }
            return score;
        }
        if (score > maxScore) {
            maxScore = score;
        }
    }
    return maxScore;
}

int SingleGame::getMinScore(int level, int currentMaxScore) {
    if (level == 0) return calcScore();

    QVector<Step *> steps;
    getAllPossibleStep(steps);
    int minScore = 100000;

    while (steps.count()) {
        Step *step = steps.back();
        steps.removeLast();

        fakeMove(step);
        int score = getMaxScore(level - 1, minScore); // calcScore(); //
        unfakeMove(step);

        delete step;

        if (score <= currentMaxScore) {
            //清空steps
            while (steps.count()) {
                Step *step = steps.back();
                steps.removeLast();
                delete step;
            }
            return score;
        }
        if (score < minScore) {
            minScore = score;
        }
    }
    //    qDebug() << "oppnent worse step , Score:" << minScore;
    return minScore;
}
Step *SingleGame::getBestMove() {
    // 1获取所有可以走的步
    QVector<Step *> steps;
    getAllPossibleStep(steps);

    qDebug() << "steps count :" << steps.count();
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
            qDebug() << "find better step , Score:" << score;
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

                if (killId != -1) {
                    if (_s[i]._red == _s[killId]._red) continue;
                }

                if (canMove(i, col, row, killId)) {
                    saveStep(i, killId, col, row, steps);
                }
            }
        }
    }
}

void SingleGame::saveStep(int moveId, int killId, int col, int row, QVector<Step *> &steps) {
    // getColRow() ;
    int row1 = _s[moveId]._row;
    int col1 = _s[moveId]._col;
    Step *step = new Step;
    step->_colFrom = col1;
    step->_rowFrom = row1;
    step->_rowTo = row;
    step->_colTo = col;
    step->_killid = killId;
    step->_moveid = moveId;

    steps.append(step);
}

void SingleGame::fakeMove(Step *step) {
    killStone(step->_killid);
    moveStone(step->_moveid, step->_colTo, step->_rowTo);
}

void SingleGame::unfakeMove(Step *step) {
    reliveStone(step->_killid);
    moveStone(step->_moveid, step->_colFrom, step->_rowFrom);
}

int SingleGame::calcScore() {
    //    enum TYPE         { CHE, MA, XIANG, SHI, JIANG, BING, PAO };
    static int chessScore[] = {100, 50, 20, 20, 1550, 10, 51};
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
// void SingleGame::mouseReleaseEvent(QMouseEvent *event) {

//    MyWidget::mouseReleaseEvent(event);
//    //电脑执黑
//    if (!bTranRed) {
//        QTimer::singleShot(100, [=]() {
//            Step *step = getBestMove();
//            //电脑走棋
//            killStone(step->_killid);
//            moveStone(step->_moveid, step->_colTo, step->_rowTo);
//            delete step;
//            judgeGameOver();
//            update();
//        });
//    }
//}

void SingleGame::click(int id, int col, int row) {
    MyWidget::click(id, col, row);
    //电脑执黑
    if (!bTranRed) {
        QTimer::singleShot(100, [=]() {
            Step *step = getBestMove();
            //电脑走棋
            killStone(step->_killid);
            moveStone(step->_moveid, step->_colTo, step->_rowTo);
            delete step;
            judgeGameOver();
            update();
        });
    }
}
