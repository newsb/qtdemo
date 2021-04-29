#include "myfish.h"

#include <QDebug>
#include <QGraphicsScene>
#include <QPainter>
#include <QRandomGenerator>

MyFish::MyFish(const QString &filename, QGraphicsScene *scene)
    : MyPixmapItem(filename, scene)
    {
    setPos(-scene->width() / 2, scene->height() - QRandomGenerator::global()->bounded(300) );
    //    setPos(0, 0);
}

//#include <QTime>
void MyFish::death() {
    //    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));          //设置随机数种子
    //    int value=qrand() % 300;
    quint32 value =200 + QRandomGenerator::global()->bounded(300) ;

    setPos(-100, value);
//    qDebug()<<value;
}

void MyFish::advance(int) {
    if (mapToScene(0, 0).y() <= 0 || mapToScene(0, 0).x() >= 800 || mapToScene(0, 0).y() >= 800) {
        setPos(-130, 200 + QRandomGenerator::global()->bounded(300));
    } else {
//        int speed = rand() % 10;
        int speed = QRandomGenerator::global()->bounded(10) ;
        if (speed % 2 == 0) {
            setPos(mapToScene(speed, -2));
        } else {
            setPos(mapToScene(speed, 2));
        }
    }
}

void MyFish::paint(QPainter *painter, const QStyleOptionGraphicsItem *, QWidget *) {
    char filename[50] = "0";
    static int i = 2;
    if (i == 4) i = 1;

    sprintf(filename, "res/shark_r%d.png", i++);

    bool ret = pix.load(filename);
    if (!ret) {
        qDebug() << "res not found :" << filename;
        return;
    }

    //    MyPixmapItem::paint(painter, option, widget);
    painter->drawPixmap(-pix.width() / 2, -pix.height(), pix);
}
