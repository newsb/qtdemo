#ifndef GRADIENTDEMO_H
#define GRADIENTDEMO_H

#include <QWidget>

class GradientDemo : public QWidget
{
    Q_OBJECT
public:
    explicit GradientDemo(QWidget *parent = nullptr);

signals:


    // QWidget interface
protected:
    virtual void paintEvent(QPaintEvent *event) override;
};

#endif // GRADIENTDEMO_H
