#include <QAbstractItemModel>
#include <QAbstractItemView>
#include <QApplication>
#include <QDirModel>
#include <QItemSelectionModel>
#include <QListView>
#include <QSplitter>
#include <QTableView>
#include <QTreeView>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

    //●QDirModel model:新建-个QDirModel对象，为数据访问做准备，QDirModel
    //的创建还可以设置过滤器，即只有符合条件的文件或目录才可被访问。
    // QDirModel类继承自QAbstractItemModel类，为访问本地文件系统提供数据模型，它提供了如新建、删除、创建目录等一系列与文件操作相关的函数
    //    ，此处只是用来显示本地文件系统。
    QDirModel model;
    //●QTreeView tree、QListView list、QTableView table:新建三种不同的View 对象，以便文件目录可以以三种不同的方式显示。
    QTreeView tree;
    QListView list;
    QTableView table;
    //调用 setModel()函数设置View 对象的Model 为 QDirModel对象的model。
    tree.setModel(&model);
    list.setModel(&model);
    table.setModel(&model);
    //设置 QTreeView对象的选择方式为多选。
    tree.setSelectionMode(QAbstractItemView::MultiSelection);
    //设置list和table与tree使用相同的选择模型
    list.setSelectionModel(tree.selectionModel());
    table.setSelectionModel(tree.selectionModel());
    //双击tree的目录时，list和table显示当前选中目录下的所有文件和文件夹
    QObject::connect(&tree, SIGNAL(doubleClicked(QModelIndex)), &list, SLOT(setRootIndex(QModelIndex)));
    QObject::connect(&tree, SIGNAL(doubleClicked(QModelIndex)), &table, SLOT(setRootIndex(QModelIndex)));
    QSplitter *splitter = new QSplitter;
    splitter->addWidget(&tree);
    splitter->addWidget(&list);
    splitter->addWidget(&table);
    splitter->setWindowTitle(QObject::tr("Model/View"));
    splitter->show();
    return a.exec();
}
