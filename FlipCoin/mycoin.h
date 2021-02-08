#ifndef MYCOIN_H
#define MYCOIN_H

#include <QPushButton>

class MyCoin : public QPushButton
{
    Q_OBJECT
public:
    MyCoin(QString img);
    void resetImg(QString img);
    int min=0;
    int max=5;
    void changeFlag();
    bool flag;

    int posX;
    int posY;
    bool isWin=false;//是否胜利

private:
    QTimer * timer1;
    QTimer * timer2;
    bool isAnimation=false;
signals:


    // QWidget interface
protected:
    void mousePressEvent(QMouseEvent *event) override;
};

#endif // MYCOIN_H
