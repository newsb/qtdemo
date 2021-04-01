#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow) {
    ui->setupUi(this);

    myScene = new QGraphicsScene(-400, -300, 800, 600);

    myScene->addText("<h1>xixi</h1>");

    QGraphicsPixmapItem *pixmap = myScene->addPixmap(QPixmap(":/res/down.png"));

    QPen pen(Qt::red);
    pen.setWidth(5);
    QBrush brush(Qt::green);
    brush.setStyle(Qt::Dense6Pattern);
    QGraphicsEllipseItem *item = myScene->addEllipse(70, 70, 111, 111, pen, brush);
    item->setFlag(QGraphicsItem::ItemIsMovable); //可拖动

    myItem = new MyItem();
    myScene->addItem(myItem);
    // myItem->show();
    ui->graphicsView->setScene(myScene);
    // QGraphicsScene 和 QGraphicsView 会自动进行坐标转换
    myView = new MyView();
    myView->setScene(myScene);
    myView->show();
}

MainWindow::~MainWindow() { delete ui; }
