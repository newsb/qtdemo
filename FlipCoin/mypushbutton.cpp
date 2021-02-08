#include "mypushbutton.h"
#include <QPainter>
#include <QPixmap>
#include <QDebug>
#include <QPropertyAnimation>

#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

MyPushButton::MyPushButton(QString normalImgPath, QString pressImgPath)
{
    this->mNormalImg=normalImgPath;
    this->mPressImg=pressImgPath;

    QPainter p(this);
    QPixmap pix;
    bool ret=pix.load(this->mNormalImg);
    if (!ret){
        QString str=QString("res not found:%1").arg(this->mNormalImg);
        cout << str;
        return;
    }

    //4句设置不规则控件：
    setFixedSize(pix.width(),pix.height());
    setStyleSheet("QPushButton {border: 0px;}");
    setIcon(pix);
    setIconSize(QSize(width(),height()));



}

void MyPushButton::room1()
{
    QPropertyAnimation *anim =new QPropertyAnimation(this,"geometry");
    anim->setDuration(200);
    anim->setStartValue(QRect(this->x(),this->y(),width(),height()));
    anim->setEndValue(QRect(this->x(),this->y()+10,width(),height()));
    //设置动画曲线
    anim->setEasingCurve(QEasingCurve::OutBounce);
    //启动动画，执行完后自动删除动画对象
    anim->start(QAbstractAnimation::DeleteWhenStopped);
}

void MyPushButton::room2()
{
    QPropertyAnimation *anim =new QPropertyAnimation(this,"geometry");
    anim->setDuration(200);
    anim->setStartValue(QRect(this->x(),this->y()+10,width(),height()));
    anim->setEndValue(QRect(this->x(),this->y(),width(),height()));
    //设置动画曲线
    anim->setEasingCurve(QEasingCurve::OutBounce);
    //启动动画，执行完后自动删除动画对象
    anim->start(QAbstractAnimation::DeleteWhenStopped);

}

void MyPushButton::mousePressEvent(QMouseEvent *event)
{
    if (this->mPressImg!=""){
        QPainter p(this);
        QPixmap pix;
        bool ret=pix.load(this->mPressImg);
        if (!ret){
            QString str=QString("res not found:%1").arg(this->mPressImg);
            cout << str;
            return;
        }

        //4句设置不规则控件：
        setFixedSize(pix.width(),pix.height());
        setStyleSheet("QPushButton {border: 0px;}");
        setIcon(pix);
        setIconSize(QSize(width(),height()));
    }
    //只按下只切图，不拦截事件
    QPushButton::mousePressEvent(event);
}

void MyPushButton::mouseReleaseEvent(QMouseEvent *event)
{
    if (this->mNormalImg!=""){
        QPainter p(this);
        QPixmap pix;
        bool ret=pix.load(this->mNormalImg);
        if (!ret){
            QString str=QString("res not found:%1").arg(this->mNormalImg);
            cout << str;
            return;
        }

        //4句设置不规则控件：
        setFixedSize(pix.width(),pix.height());
        setStyleSheet("QPushButton {border: 0px;}");
        setIcon(pix);
        setIconSize(QSize(width(),height()));
    }
    //只按下只切图，不拦截事件
    QPushButton::mouseReleaseEvent(event);
}
