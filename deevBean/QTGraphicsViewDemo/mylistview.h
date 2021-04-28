#ifndef MYLISTVIEW_H
#define MYLISTVIEW_H

#include <QWidget>
#include <QStringListModel>
#include <QListView>
#include <QHBoxLayout>
#include <QPushButton>

//////////////QStringListModel //////////////
/*
     * QStringListModel是最简单的模型类，具备向视图提供字符串数据的能力。
     * QStringListModel是一个可编辑的模型，可以为组件提供一系列字符串作为数据
     * 我们可以将其看作是封装了QStringList的模型。
     * QStringList是一种很常用的数据类型，实际上是一个字符串列表（也就是QList<QString>）。
     * 既然是列表，它也就是线性的数据结构，因此，QStringListModel很多时候都会作为QListView或者QComboBox这种只有一列的视图组件的数据模型。
     * 下面我们通过一个例子来看看QStringListModel的使用。首先是我们的构造函数：
     */
class MyListView : public QWidget
{
    Q_OBJECT
public:
    explicit MyListView(QWidget *parent = nullptr);
    QStringListModel *model;
    QListView *listView;
    void insertData();
    void deleteData();
    void showData();
signals:

};

#endif // MYLISTVIEW_H
