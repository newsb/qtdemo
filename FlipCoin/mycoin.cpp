#include "mycoin.h"

#include <QDebug>
#include <QTimer>

#define cout qDebug() << "[" << __FILE__ << ":" << __LINE__ << "]"

MyCoin::MyCoin(QString img) {
    QPixmap pix;
    bool ret = pix.load(img);
    if (!ret) {
        QString str = QString("image load failed:%1").arg(img);
        cout << str;
        return;
    }

    setFixedSize(pix.width(), pix.height());
    setStyleSheet("QPushButton{border: 0px;}");
    setIcon(pix);
    setIconSize(QSize(pix.width(), pix.height()));

    this->timer1 = new QTimer(this);
    this->timer2 = new QTimer(this);
    //监听翻银币的定时器
    connect(this->timer1, &QTimer::timeout, [=]() {
        QPixmap pix;
        QString str = QString(":/res/coin%1.png").arg(this->min++);
        bool ret = pix.load(str);
        if (!ret) {
            QString str = QString("image load failed:%1").arg(str);
            cout << str;
            return;
        }

        setFixedSize(pix.width(), pix.height());
        setStyleSheet("QPushButton{border: 0px;}");
        setIcon(pix);
        setIconSize(QSize(pix.width(), pix.height()));

        if (this->min > this->max) {
            this->min = 0;
            this->timer1->stop();
            isAnimation = false;
        }
    });
    //监听翻金币的定时器
    connect(this->timer2, &QTimer::timeout, [=]() {
        QPixmap pix;
        QString str = QString(":/res/coin%1.png").arg(this->max--);
        bool ret = pix.load(str);
        if (!ret) {
            QString str = QString("image load failed:%1").arg(str);
            cout << str;
            return;
        }

        setFixedSize(pix.width(), pix.height());
        setStyleSheet("QPushButton{border: 0px;}");
        setIcon(pix);
        setIconSize(QSize(pix.width(), pix.height()));

        if (this->max < this->min) {
            this->max = 5;
            this->timer2->stop();
            isAnimation = false;
        }
    });
}

void MyCoin::resetImg(QString img) {
    QPixmap pix;
    bool ret = pix.load(img);
    if (!ret) {
        QString str = QString("image load failed:%1").arg(img);
        cout << str;
        return;
    }

    setFixedSize(pix.width(), pix.height());
    setStyleSheet("QPushButton{border: 0px;}");
    setIcon(pix);
    setIconSize(QSize(pix.width(), pix.height()));
}

//点击硬币 改变硬币的标志
void MyCoin::changeFlag() {
    if (flag) {
        timer1->start(48);
        flag = false;
    } else {
        timer2->start(48);
        flag = true;
    }
    isAnimation = true;
}

void MyCoin::mousePressEvent(QMouseEvent *event) {
    if (isAnimation || isWin) {
        cout << "isAnimation=" << isAnimation << ",isWin=" << isWin;
        return;
    } else {
        QPushButton::mousePressEvent(event);
    }
}
