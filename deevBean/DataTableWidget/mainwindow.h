#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QVBoxLayout>
#include "datatablewidget.h"

#include <QMainWindow>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    DataTableWidget *topTable; DataTableWidget *bottomTable; QVBoxLayout *layout;

signals:

};

#endif // MAINWINDOW_H
