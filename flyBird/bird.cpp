#include "bird.h"
#include <QDebug>

Bird::Bird(QWidget *parent)
    : QWidget(parent) {
    for (int i = 0; i < 30; i++) {
        QString str = QString(":/res/gif_%1.png").arg(i);
        bool ret = mPix.load(str);
        if (!ret) {
            qDebug() << "load image failed:" << str;
        }
    }
    this->setFixedSize(mPix.width(), mPix.height());

    this->mTimer = new QTimer(this);
    connect(mTimer, &QTimer::timeout, [=]() {
        QString str = QString(":/res/gif_%1.png").arg(min++);
        this->mPix.load(str);

        if (this->min > this->max) {
            this->min = 0;
        }

        emit changePix();
    });

    m_menu = new QMenu();
    connect(m_menu->addAction("exit"), &QAction::triggered, [=]() { exit(0); });

    speedX = 1 + rand() % (3);
    speedY = 1 + rand() % (3);
}

void Bird::running() { this->mTimer->start(50); }

void Bird::mousePressEvent(QMouseEvent *event) {
    m_pos = event->globalPos() - ((QWidget *)(this->parent()))->frameGeometry().topLeft();
    isMouseDown = true;

    //如果是右键按下，弹出菜单
    if (event->button() == Qt::RightButton) {
        this->m_menu->popup(QCursor::pos());
    }
    //右键菜单的弹出消失后，重置按下状态，否则鸟不动了
    connect(m_menu, &QMenu::aboutToHide, [=]() { this->isMouseDown = false; });
}

void Bird::mouseMoveEvent(QMouseEvent *event) {
    //获取到窗口移动的位置
    emit moving(event->globalPos() - this->m_pos);
}

void Bird::mouseReleaseEvent(QMouseEvent *) { isMouseDown = false; }
