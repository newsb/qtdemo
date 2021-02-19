#include "mynet.h"
#include "myfish.h"

MyNet::MyNet(const QString &filename, QGraphicsScene *scene)
    : MyPixmapItem(filename, scene) {}

void MyNet::advance(int) {
    if (this->collidingItems().count() > 0) {
        QList<QGraphicsItem *> list = collidingItems();
        QList<QGraphicsItem *>::Iterator i;
        MyFish *fish;
        i = list.begin();
        while (i != list.end()) {

            fish = (MyFish *)(*i);

            fish->death(); // delete fish;

            i++;
        }
    }

    this->hide();
    delete this;
}
