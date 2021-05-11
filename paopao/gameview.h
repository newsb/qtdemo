#ifndef GAMEVIEW_H
#define GAMEVIEW_H

#include <QObject>
#include <QGraphicsView>
#include <QGraphicsScene>
#include "player.h"

#include "mypaopao.h"
#include "cell.h"
#include "global.h"

class GameView : public QGraphicsView
{
    Q_OBJECT
public:
    explicit GameView(QWidget *parent = nullptr);

signals:

private:
    void setBubbleAt(QPoint pt);
    ATTR attrAt(int row,int col);
    ATTR attrAt(QPoint pt);
    QGraphicsScene *mScene;
    Player * mPlayer;
    QList<MyPaoPao*> mPaoPaoList;
    Cell * mMap[ROW][COL];

    void initGameData();
protected:
    virtual void drawBackground(QPainter *painter, const QRectF &rect) override;

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // GAMEVIEW_H
