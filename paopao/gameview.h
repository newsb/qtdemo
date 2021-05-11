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

    QGraphicsScene *mScene;
    Player * mPlayer;
    QList<MyPaoPao*> mPaoPaoList;
    Cell mMap[ROW][COL];

    void initGameData();
protected:
    virtual void drawBackground(QPainter *painter, const QRectF &rect) override;

    // QWidget interface
protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
};

#endif // GAMEVIEW_H
