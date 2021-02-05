#ifndef PLAYSCENE_H
#define PLAYSCENE_H

#include <QMainWindow>

#include "mycoin.h"
#include "mypushbutton.h"

class PlayScene : public QMainWindow
{
    Q_OBJECT
public:
    PlayScene(int index);
    MyCoin* coinBtn[4][4];
    bool isWin = true; //是否胜利
private:
    int levelIndex;
    MyPushButton* mBackBtn;
    int gameArray[4][4];
signals:
    void quitSignal();

protected:
    void paintEvent(QPaintEvent* event) override;
};

#endif // PLAYSCENE_H
