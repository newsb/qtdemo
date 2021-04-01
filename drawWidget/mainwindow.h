#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "drawwidget.h"
#include <QComboBox>
#include <QLabel>
#include <QMainWindow>
#include <QSpinBox>
#include <QToolButton>

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
    void createToolBar();

  private:
    Ui::MainWindow *ui;
    DrawWidget *drawWidget;

    QLabel *styleLabel;
    QComboBox *styleComboBox;
    QLabel *widthLabel;
    QSpinBox *widthSpinBox;
    QToolButton *colorBtn;
    QToolButton *clearBtn;
  public slots:
    void ShowStyle();
    void ShowColor();
};
#endif // MAINWINDOW_H
