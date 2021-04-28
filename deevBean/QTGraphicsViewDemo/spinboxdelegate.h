#ifndef SPINBOXDELEGATE_H
#define SPINBOXDELEGATE_H

#include <QStyledItemDelegate>

/*
 * 委托就是供视图实现某种高级的编辑功能。不同于经典的 Model-View-Controller（MVC）模式，model/view 没有将用户交互部分完全分离。
 * 一般地，视图将数据向用户进行展示并且处理通用的输入。
 * 但是，对于某些特殊要求（比如这里的要求必须输入数字），则交予委托完成。这些组件提供输入功能，同时也能渲染某些特殊数据项。
 * 委托的接口由QAbstractItemDelegate定义。在这个类中，委托通过paint()和sizeHint()两个函数渲染用户内容（也就是说，你必须自己将渲染器绘制出来）。
 * 为使用方便，从 4.4 开始，Qt 提供了另外的基于组件的子类：QItemDelegate和QStyledItemDelegate。默认的委托是QStyledItemDelegate。
 * 二者的区别在于绘制和向视图提供编辑器的方式。
 * QStyledItemDelegate使用当前样式绘制，并且能够使用 Qt Style Sheet（我们会在后面的章节对 QSS 进行介绍），
 * 因此我们推荐在自定义委托时，使用QStyledItemDelegate作为基类。不过，除非自定义委托需要自己进行绘制，否则，二者的代码其实是一样的。
 *继承QStyledItemDelegate需要实现以下几个函数：
 *  createEditor()：返回一个组件。该组件会被作为用户编辑数据时所使用的编辑器，从模型中接受数据，返回用户修改的数据。
 *  setEditorData()：提供上述组件在显示时所需要的默认值。
 *  updateEditorGeometry()：确保上述组件作为编辑器时能够完整地显示出来。
 *  setModelData()：返回给模型用户修改过的数据。
 *
 */
class SpinBoxDelegate : public QStyledItemDelegate
{
     Q_OBJECT
public:
    SpinBoxDelegate(QObject *parent = 0) : QStyledItemDelegate(parent) {}

    QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                          const QModelIndex &index) const;

    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    void setModelData(QWidget *editor, QAbstractItemModel *model,
                      const QModelIndex &index) const;

    void updateEditorGeometry(QWidget *editor,
                              const QStyleOptionViewItem &option,
                              const QModelIndex &index) const;
};

#endif // SPINBOXDELEGATE_H
