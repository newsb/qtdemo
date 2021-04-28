#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QGraphicsScene>
#include <QGraphicsView>
QT_BEGIN_NAMESPACE
//namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void adjustViewSize();
private:
//    Ui::MainWindow *ui;

    void initScene();
    void initSceneBackground();

    QGraphicsScene *scene;
    QGraphicsView *view;

//    GameController *game;
};
#endif // MAINWINDOW_H
