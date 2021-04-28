#ifndef BOOLEANWINDOW_H
#define BOOLEANWINDOW_H

#include <QWidget>

#include <QLabel>
#include <QLineEdit>
#include <QTreeView>
#include <QGridLayout>
#include "booleanmodel.h"

class BooleanWindow : public QWidget
{
    Q_OBJECT
public:
    explicit BooleanWindow(QWidget *parent = nullptr);

    QLabel *label;QLineEdit*lineEdit;BooleanModel *booleanModel;QTreeView *treeView;

    void booleanExpressionChanged(const QString &expr);
signals:

};

#endif // BOOLEANWINDOW_H
