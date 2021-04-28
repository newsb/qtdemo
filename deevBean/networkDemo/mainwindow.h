#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include "networker.h"

#include <QMainWindow>
#include <QPushButton>

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    QPushButton* refreshButton;
        QPushButton*refreshButton2;
private:
    class Private;
    friend class Private;
    Private *d;
signals:

};

#endif // MAINWINDOW_H
