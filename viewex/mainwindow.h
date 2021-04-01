#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QAction>
#include <QMainWindow>
#include <QMenu>
#include <QMenuBar>
#include <QSplitter>
#include <QStandardItemModel>
#include <QTableView>

#include "histogramview.h"

class MainWindow : public QMainWindow {
    Q_OBJECT

  public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void createAction();
    void createMenu();
    void setupModel();
    void setupView();

    void openFile(QString);
    void saveFile(QString);
    void fileFun(QString);
  public slots:
    void slotOpen();
    void slotSave();

  private:
    HistogramView *histogram;

    QMenu *fileMenu;
    QAction *openAct, *saveAct;
    QStandardItemModel *model;
    QTableView *table;
    QSplitter *splitter;
};
#endif // MAINWINDOW_H
