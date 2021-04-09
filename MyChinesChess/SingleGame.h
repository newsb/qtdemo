#ifndef SINGLEGAME_H
#define SINGLEGAME_H
#include "MyWidget.h"
#include "Step.h"
#include <QVector>

class SingleGame : public MyWidget {
  public:
    SingleGame();

    // QWidget interface
  protected:
    int _level = 3;
    //    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    Step *getBestMove();
    void getAllPossibleStep(QVector<Step *> &steps);

    void fakeMove(Step *step);
    int calcScore();
    int getMinScore(int level, int currentMaxScore);
    int getMaxScore(int level, int currentMinScore);

    // MyWidget interface
  protected:
    virtual void click(int id, int col, int row) override;
};

#endif // SINGLEGAME_H
