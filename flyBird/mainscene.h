#ifndef MAINSCENE_H
#define MAINSCENE_H

#include <QWidget>
#include "bird.h"

class MainScene : public QWidget
{
    Q_OBJECT

public:
    MainScene(QWidget *parent = nullptr);
    ~MainScene();
private:
    Bird * mBird;

    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};
#endif // MAINSCENE_H
