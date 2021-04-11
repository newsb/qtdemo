#ifndef MYWIDGET_H
#define MYWIDGET_H

#include "mystone.h"
#include <QPainter>
#include <QPainterPath>
#include <QWidget>
#include "Step.h"
#include <QSound>
class MyWidget : public QWidget {
    Q_OBJECT
  public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

    const int COL_COUNT = 8;
    const int ROW_COUNT = 9;

    const int PADDING_LEFT = 20;
    const int PADDING_RIGHT = 150;
    const int PADDING_TOP = 20;
    const int PADDING_BOTTOM = 20;

    void init(bool bRedSide);
    //当前该红棋走了
    bool bTranRed;
    //棋子半径
    double _r;
    //棋盘格子高、宽
    double mColumnWidth, mRowHeight;
    MyStone _s[32],_ss[32];
    int selectId = -1; //选择的棋子id
    int m_winner = 0;  // 0:未结束； 1：红棋赢；2：黑旗赢

    bool _bRedSide; //红棋在下面
    virtual void click(int id, int col, int row);

    // half=0：全部；half=1：左半侧；half=2右半侧
    QPainterPath getPaoBingPostionPath(QPoint &point, int half = 0) const;
    bool isBottomSide(int id);

    //根据棋子id，算出它的中心坐标
    virtual QPointF center(int id );
    //根据坐标，计算行列
    bool getColRow(QPoint pt, int &col, int &row);
    //获取col、row位置的棋子
    MyStone *getStoneAt(int col, int row);
    int getStoneIdAt(int col, int row);
    void moveStone(int moveId, int col, int row);
    void killStone(int killId);
    void reliveStone(int killId);
    //同一行的两个列数之间棋子数
    int countStoneAtCol(int row, int col1, int col2);
    int countStoneAtRow(int col, int row1, int row2);
    bool canSelect();
    int judgeGameOver();
    bool canMove(int moveId, int col, int row, int killId);

protected:
    int mUseTime;

    QSound * bells;
    void saveStep(int moveId, int killId, int col, int row, QVector<Step *> &steps);
    QVector<Step *>  mPassSteps;
//    void logStep(int moveId, int killId, int col, int row);
    void unfakeMove(Step *step);
    void repentanceStep(int backCount);

    bool isLost(bool bRed);
    //bRed=true:判断红棋，false：判断黑棋
    bool isJIANGDead(bool bRed);
    bool cannotMoveAnyStone(bool bRed);
    void iAmLost(bool bRed);
  private:
      QRect mBackRect,mRepentanceRect,mUseTimeRect;
      bool bMouseOnBtn=false,bMouseOnBtn1=false;
      int mUseTimeId;

    void drawBoard(QPainter &painter);
    void drawGameResult(QPainter &painter);
    void drawGameBtns(QPainter &painter);
    bool canMoveCHE(int moveId, int col, int row, int killId);
    bool canMoveMA(int moveId, int col, int row, int killId);
    bool canMoveXIANG(int moveId, int col, int row, int killId);
    bool canMoveSHI(int moveId, int col, int row, int killId);
    bool canMoveJIANG(int moveId, int col, int row, int killId);
    bool canMovePAO(int moveId, int col, int row, int killId);
    bool canMoveBING(int moveId, int col, int row, int killId);


    // QObject interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void resizeEvent(QResizeEvent *event) override;
    virtual void timerEvent(QTimerEvent *event) override;
    //画棋子
    virtual void drawStone(QPainter &painter, int id);
 signals:
     void back_signal();
     void repentance_signal(int backCount);


};
#endif // MYWIDGET_H
