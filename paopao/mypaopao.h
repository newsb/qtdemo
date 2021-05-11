#ifndef MYPAOPAO_H
#define MYPAOPAO_H

#include <QGraphicsObject>
class MyPaoPao : public QGraphicsObject
{
    Q_OBJECT
    Q_PROPERTY(QColor color MEMBER m_color READ color WRITE setColor NOTIFY colorChanged)
public:
    MyPaoPao(QGraphicsItem *parent = nullptr);

    QColor color();
    void setColor(QColor color);

signals:
    void colorChanged();

protected:
    QColor m_color;

public:
    virtual QRectF boundingRect() const override;
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget) override;

private:
    QPixmap *mPix;
};

#endif // MYPAOPAO_H
