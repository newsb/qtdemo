#ifndef CHOOSE_SCENE_H
#define CHOOSE_SCENE_H

#include <QMainWindow>
#include "mypushbutton.h"
#include "playscene.h"

class ChooseScene : public QMainWindow
{
    Q_OBJECT
public:
    explicit ChooseScene(QWidget *parent = nullptr);
   // void paintEvent( )
signals:
    void quitSignal();
private:
    MyPushButton *mBackBtn;
    // QWidget interface
    PlayScene * pScene;
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // CHOOSE_SCENE_H
