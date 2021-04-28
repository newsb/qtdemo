#ifndef FILESYSTEMWIDGET_H
#define FILESYSTEMWIDGET_H

#include <QWidget>
#include <QFileSystemModel>
#include <QTreeView>
#include <QPushButton>
#include <QHBoxLayout>

class FileSystemWidget : public QWidget
{
    Q_OBJECT
public:
    explicit FileSystemWidget(QWidget *parent = nullptr);
    QFileSystemModel *model;
    QTreeView *treeView;

    QPushButton *mkdirButton ;
    QPushButton *rmButton ;
    QHBoxLayout *buttonLayout ;

    void mkdir();
    void rm();
signals:

};

#endif // FILESYSTEMWIDGET_H
