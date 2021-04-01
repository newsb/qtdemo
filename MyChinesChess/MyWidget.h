#ifndef MYWIDGET_H
#define MYWIDGET_H

#include "mystone.h"
#include <QPainter>
#include <QPainterPath>
#include <QWidget>
class MyWidget : public QWidget {
    Q_OBJECT

  public:
    MyWidget(QWidget *parent = nullptr);
    ~MyWidget();

    const int COL_COUNT = 8;
    const int ROW_COUNT = 9;
    // QWidget interface
  protected:
    virtual void paintEvent(QPaintEvent *event) override;

    void init(bool bRedSide);
    //当前该红棋走了
    bool bTranRed;
    //棋子半径
    int _r;
    //棋盘格子高、宽
    int mColumnWidth, mRowHeight;
    MyStone _s[32];
    int selectId = -1; //选择的棋子id
    int m_winner = 0;  // 0:未结束； 1：红棋赢；2：黑旗赢

    bool _bRedSide; //红棋在下面
    virtual void click(int id, int col, int row);

    // half=0：全部；half=1：左半侧；half=2右半侧
    QPainterPath getPaoBingPostionPath(QPoint &point, int half = 0) const;
    bool isBottomSide(int id);

    //画棋子
    void drawStone(QPainter &painter, int id);
    //根据棋子id，算出它的中心坐标
    QPoint center(int id);
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
    bool canMove(int moveId, int col, int row, int killId);

    bool canMoveCHE(int moveId, int col, int row, int killId);
    bool canMoveMA(int moveId, int col, int row, int killId);
    bool canMoveXIANG(int moveId, int col, int row, int killId);
    bool canMoveSHI(int moveId, int col, int row, int killId);
    bool canMoveJIANG(int moveId, int col, int row, int killId);
    bool canMovePAO(int moveId, int col, int row, int killId);
    bool canMoveBING(int moveId, int col, int row, int killId);

    void judgeGameOver();
    // QWidget interface
  protected:
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
};
#endif // MYWIDGET_H