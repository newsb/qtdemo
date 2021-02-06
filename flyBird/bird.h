#ifndef BIRD_H
#define BIRD_H

#include <QWidget>
#include <QPixmap>

class Bird : public QWidget
{
    Q_OBJECT
public:
    explicit Bird(QWidget *parent = nullptr);
private:
    QPixmap mPix;
signals:


    // QWidget interface
protected:
    void paintEvent(QPaintEvent *event) override;
};

#endif // BIRD_H
