#ifndef MYBULLET_H
#define MYBULLET_H

#include <QObject>

class MyBullet : public QObject {
    Q_OBJECT
  public:
    explicit MyBullet(QObject *parent = nullptr);

  signals:
};

#endif // BULLET_H
