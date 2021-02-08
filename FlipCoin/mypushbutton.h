#ifndef MYPUSHBUTTON_H
#define MYPUSHBUTTON_H

#include <QMouseEvent>
#include <QPushButton>

class MyPushButton : public QPushButton
{
    Q_OBJECT
public:
    MyPushButton(QString normalImgPath,QString pressImgPath="");
    void room1();
    void room2();
private:
    QString mNormalImg,mPressImg;

signals:


    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;

    // QWidget interface
protected:
    void mouseReleaseEvent(QMouseEvent *event) override;
};

#endif // MYPUSHBUTTON_H
