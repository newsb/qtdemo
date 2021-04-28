#include "mymainwindow.h"
#include <gradientdemo.h>
#include <QApplication>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "myfiledemo.h"
#include <QDir>
#include <QDebug>
#include "filesystemwidget.h"
#include "mylistview.h"
#include "sortview.h"
#include <QTableView>
#include "currencymodel.h"
#include "booleanwindow.h"
#include "mainwindow.h"
#include "projectlistwidget.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyMainWindow w;
    w.show();

    QGraphicsScene scene;
    scene.addLine(0, 0, 150, 150);
    scene.setSceneRect(0, 0, 300, 300);// sceneRect确定 QGraphicsView默认的滚动条区域，并且协助QGraphicsScene管理元素索引。
    QGraphicsView view(&scene);
    view.setWindowTitle("Graphics View");
//    view.resize(500, 500);
    view.show();

    GradientDemo w1;
    w1.show();

    qDebug()<< a.applicationFilePath() ;
    qDebug()<<a.applicationDirPath() ;
    qDebug()<<QDir::currentPath() ;
    MyFileDemo w2;
    w2.show();


    FileSystemWidget fsw;
    fsw.show();
    MyListView lv;
    lv.show();

    SortView sv;
    sv.show();


///////////////////自定义只读模型/////////////////////////////////
    QMap<QString, double> data;
    data["USD"] = 1.0000;
    data["CNY"] = 0.1628;
    data["GBP"] = 1.5361;
    data["EUR"] = 1.2992;
    data["HKD"] = 0.1289;
    QTableView view1;
    CurrencyModel *model = new CurrencyModel(&view1);
    model->setCurrencyMap(data);
    view1.setModel(model);
    view1.resize(400, 300);
    view1.show();
////////////////////////////////////////////////////

    BooleanWindow bw;
    bw.show();
    ///////////////////drag and drop/////////////////////////////////
    MainWindow mw;
    mw.show();
//    ProjectListWidget plw ;
//    plw.show();
    return a.exec();
}
