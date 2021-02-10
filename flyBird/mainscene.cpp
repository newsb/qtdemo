#include "mainscene.h"
#include <QApplication>
#include <QDesktopWidget>
#include <QPainter>

MainScene::MainScene(QWidget *parent)
    : QWidget(parent) {

    this->mBird = new Bird(this);
    mBird->setParent(this);
    this->setFixedSize(this->mBird->width(), mBird->height());

    connect(mBird, &Bird::changePix, [=]() { update(); });

    this->mBird->running();
    //获取桌面对象
    QDesktopWidget *desk = QApplication::desktop();

    // bird moving
    connect(mBird, &Bird::moving, [=](QPoint point) {
        m_Auto_Pos = point;
        this->move(point);
    });

    //向右移动定时器
    mTimer = new QTimer(this);
    connect(mTimer, &QTimer::timeout, [=]() {
        if (mBird->isMouseDown != true) {
            if (m_Auto_Pos.x() < 0 || m_Auto_Pos.x() > desk->width() - mBird->width()) {
                mBird->speedX = -mBird->speedX;
            }

            if (m_Auto_Pos.y() < 0 || m_Auto_Pos.y() > desk->height() - mBird->height()) {
                mBird->speedY = -mBird->speedY;
            }
            m_Auto_Pos.setX(m_Auto_Pos.x() + mBird->speedX);
            m_Auto_Pos.setY(m_Auto_Pos.y() + mBird->speedY);
        }

        //        if (m_Auto_Pos.x() > desk->width()) {
        //            m_Auto_Pos.setX(-mBird->width());
        //        }
        //        if (m_Auto_Pos.y() > desk->height()) {
        //            m_Auto_Pos.setY(-mBird->height());
        //        }
        this->move(m_Auto_Pos);
    });
    mTimer->start(30);

    //标题栏去除
    setWindowFlag(Qt::FramelessWindowHint);
    //透明
    setAttribute(Qt::WA_TranslucentBackground);
    //置顶
    setWindowFlags(this->windowFlags() | Qt::WindowStaysOnTopHint);
    m_Auto_Pos.setY(desk->height() * 0.5 - mBird->height() * 0.5);
    //    m_Auto_Pos.setX(rand() % 5);
    //    m_Auto_Pos.setY(rand() % 8);
}

MainScene::~MainScene() {}

void MainScene::paintEvent(QPaintEvent *) {
    QPainter p(this);

    p.rotate(45);
    p.drawPixmap(0, 0, this->mBird->mPix);
}
