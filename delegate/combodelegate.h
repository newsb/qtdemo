#ifndef COMBODELEGATE_H
#define COMBODELEGATE_H

#include <QItemDelegate>

class ComboDelegate : public QItemDelegate {
    Q_OBJECT
  public:
    ComboDelegate(QObject *parent = 0);

    // QAbstractItemDelegate interface
  public:
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const override;
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                      const QModelIndex &index) const override;
};

#endif // COMBODELEGATE_H
