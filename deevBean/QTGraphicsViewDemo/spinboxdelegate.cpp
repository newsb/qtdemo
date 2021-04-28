#include "spinboxdelegate.h"
#include <QSpinBox>
//在createEditor()函数中，parent 参数会作为新的编辑器的父组件。
QWidget *SpinBoxDelegate::createEditor(QWidget *parent,
                                       const QStyleOptionViewItem & /* option */,
                                       const QModelIndex & /* index */) const
{
    QSpinBox *editor = new QSpinBox(parent);
    editor->setMinimum(0);
    editor->setMaximum(100);
    return editor;
}
 //setEditorData()函数从模型中获取需要编辑的数据（具有Qt::EditRole角色）。
 //由于我们知道它就是一个整型，因此可以放心地调用toInt()函数。
 //editor 就是所生成的编辑器实例，我们将其强制转换成QSpinBox实例，设置其数据作为默认值。
void SpinBoxDelegate::setEditorData(QWidget *editor,
                                    const QModelIndex &index) const
{
    int value = index.model()->data(index, Qt::EditRole).toInt();
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->setValue(value);
}

//在用户编辑完数据后，委托会调用setModelData()函数将新的数据保存到模型中。
//因此，在这里我们首先获取QSpinBox实例，得到用户输入值，然后设置到模型相应的位置。
//标准的QStyledItemDelegate类会在完成编辑时发出closeEditor()信号，视图会保证编辑器已经关闭，但是并不会销毁，因此需要另外对内存进行管理。
//由于我们的处理很简单，无需发出closeEditor()信号，但是在复杂的实现中，记得可以在这里发出这个信号。
//针对数据的任何操作都必须提交给QAbstractItemModel，这使得委托独立于特定的视图。
//当然，在真实应用中，我们需要检测用户的输入是否合法，是否能够存入模型。
void SpinBoxDelegate::setModelData(QWidget *editor,
                                   QAbstractItemModel *model,
                                   const QModelIndex &index) const
{
    QSpinBox *spinBox = static_cast<QSpinBox*>(editor);
    spinBox->interpretText();//interpretText:QSpinBox 需要解释输入框中的值
    int value = spinBox->value();
    model->setData(index, value, Qt::EditRole);
}
//最后，由于我们的编辑器只有一个数字输入框，所以只是简单将这个输入框的大小设置为单元格的大小（由option.rect提供）。
//如果是复杂的编辑器，我们需要根据单元格参数（由option提供）、数据（由index提供）结合编辑器（由editor提供）计算编辑器的显示位置和大小。
void SpinBoxDelegate::updateEditorGeometry(QWidget *editor,
                                           const QStyleOptionViewItem &option,
                                           const QModelIndex &index) const
{
    editor->setGeometry(option.rect);
}
