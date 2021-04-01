#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "myitem.h"
#include "myview.h"
#include <QGraphicsScene>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

  private:
    Ui::MainWindow *ui;
    MyView *myView;
    QGraphicsScene *myScene;
    MyItem *myItem;
};
#endif // MAINWINDOW_H
