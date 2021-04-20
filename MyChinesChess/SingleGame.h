#ifndef SINGLEGAME_H
#define SINGLEGAME_H
#include "MyWidget.h"
#include "Step.h"
#include <QVector>
#include <QMutex>
class SingleGame : public MyWidget {
    Q_OBJECT
  public:
    SingleGame(QWidget *parent = nullptr);
~SingleGame();
    // QWidget interface
  protected:
    int _level = 4;
    //    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    Step *getBestMove();
    void getAllPossibleStep(QVector<Step *> &steps);
    void getAPossibleStep(int stoneId,int col,int row,QVector<Step *> &steps);

    void fakeMove(Step *step);
    int calcScore();
    int getMinScore(int level, int currentMaxScore);
    int getMaxScore(int level, int currentMinScore);

    bool isComputerMoving=false;
    void startComputerMove();
  protected:
    virtual void click(int id, int col, int row) override;
    virtual void drawStone(QPainter &painter, int id) override;
public slots:
//    QMutex mutex;
    void updateComputerMove(Step *step);
signals:
    void computerMoveFinished(Step *step);
public:
    virtual QPointF center(int id )override;
 MyStone  _ss[32];
private:
    QMutex multex;
    bool mStopping=false;
protected:
    virtual void closeEvent(QCloseEvent *event) override;
};

#endif // SINGLEGAME_H
