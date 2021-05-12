#ifndef WIDGET_H
#define WIDGET_H

#include <QWindow>
#include <QBackingStore>

#include <QImage>
class Widget : public QWindow
{
    Q_OBJECT

public:
    Widget(QWindow *parent = nullptr);
    ~Widget();

    bool event(QEvent *) override;

private:
    QBackingStore store;
    QImage image;
    HWND GetWorkerW();
};
#endif // WIDGET_H
