#include "mywidget.h"
#include "ui_mywidget.h"

#include <QGraphicsDropShadowEffect>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
      , ui(new Ui::MyWidget)
{
    ui->setupUi(this);
    setWindowTitle("无边框窗口、可拖动窗体、窗体圆角阴影");
    // Qt::FramelessWindowHint 无边框
    setWindowFlags(Qt::FramelessWindowHint);

    //阴影边框效果类型，
    QGraphicsDropShadowEffect * shadow=new QGraphicsDropShadowEffect();
    shadow->setBlurRadius(5);
    shadow->setColor(Qt::blue);
    shadow->setOffset(0);
    ui->shadowWidget->setGraphicsEffect(shadow);
//    this->setGraphicsEffect(shadow);
    //设置父窗口透明
    this->setAttribute(Qt::WA_TranslucentBackground);
}


MyWidget::~MyWidget()
{
    delete ui;
}


#include <QMouseEvent>

void MyWidget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);

    QPoint y=event->globalPos();//鼠标相对于桌面左上角位置，全局坐标
    QPoint x=this->geometry().topLeft();//窗口左上角相对于桌面左上角位置
    z=y-x;//向量运算，拖动时z是定值，

}

void MyWidget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    z=QPoint();//清空变量z
}

void MyWidget::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);

    QPoint y=event->globalPos();//鼠标相对于桌面左上角位置，全局坐标
    QPoint x=y-z;//鼠标相对于桌面左上角位置，全局坐标

    this->move(x);
}
