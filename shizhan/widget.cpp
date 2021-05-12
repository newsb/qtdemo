#include "widget.h"
#include "ui_widget.h"

#include <QGraphicsDropShadowEffect>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);

    setWindowTitle("无边框窗口、可拖动窗体、窗体圆角阴影");
    ui->lblCaption->setText(windowTitle());

    // Qt::FramelessWindowHint 无边框
    setWindowFlags(Qt::FramelessWindowHint);

    //阴影边框效果类型，
    QGraphicsDropShadowEffect * shadow=new QGraphicsDropShadowEffect();

    shadow->setBlurRadius(15);
    shadow->setColor(Qt::blue);
    shadow->setOffset(0);

    ui->shadowWidget->setGraphicsEffect(shadow);
//    this->setGraphicsEffect(shadow);

    //设置父窗口透明
    this->setAttribute(Qt::WA_TranslucentBackground);


    this->layout()->setMargin(9);
}

Widget::~Widget()
{
    delete ui;
}



#include <QMouseEvent>

void Widget::mousePressEvent(QMouseEvent *event)
{
    QWidget::mousePressEvent(event);

    QPoint y=event->globalPos();//鼠标相对于桌面左上角位置，全局坐标
    QPoint x=this->geometry().topLeft();//窗口左上角相对于桌面左上角位置
    z=y-x;//向量运算，拖动时z是定值，

}

void Widget::mouseReleaseEvent(QMouseEvent *event)
{
    QWidget::mouseReleaseEvent(event);
    z=QPoint();//清空变量z
}

void Widget::mouseMoveEvent(QMouseEvent *event)
{
    QWidget::mouseMoveEvent(event);
    if(z==QPoint()){
        return;
    }
    QPoint y=event->globalPos();//鼠标相对于桌面左上角位置，全局坐标
    QPoint x=y-z;//鼠标相对于桌面左上角位置，全局坐标

    this->move(x);
}


void Widget::on_btnClose_clicked()
{
    this->close();
}

void Widget::on_btnMax_clicked()
{
    if (this->isMaximized()){
        this->layout()->setMargin(9);
        this->showNormal();
    }else{
        this->layout()->setMargin(0);
        this->showMaximized();
    }
}

void Widget::on_btnMin_clicked()
{
    this->showMinimized();
}
