#include "spindeledate.h"

#include <QSpinBox>

SpinDeledate::SpinDeledate(QObject *parent)
    : QItemDelegate(parent) {}

QWidget *SpinDeledate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const {
    QSpinBox *editor = new QSpinBox(parent);
    editor->setRange(0, 10000);
    editor->installEventFilter(const_cast<SpinDeledate *>(this));
    return editor;
}

void SpinDeledate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    int value = index.model()->data(index).toInt();
    QSpinBox *box = static_cast<QSpinBox *>(editor);
    box->setValue(value);
}

void SpinDeledate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    QSpinBox *box = static_cast<QSpinBox *>(editor);
    int value = box->value();
    model->setData(index, value);
}

void SpinDeledate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const {
    editor->setGeometry(option.rect);
}
