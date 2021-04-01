#ifndef DATEDELEGATE_H
#define DATEDELEGATE_H

#include <QItemDelegate>

class DateDelegate : public QItemDelegate {
    Q_OBJECT

  public:
    DateDelegate(QObject *parent = 0);
    //完成创建控件，
    virtual QWidget *createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                  const QModelIndex &index) const override;

    // 设置控件显示的数据，将model中数据更新到Delegate中，相当于一个初始化工作
    virtual void setEditorData(QWidget *editor, const QModelIndex &index) const override;

    // 将Delegate中的数据的改变更新到model
    virtual void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const override;

    // 更新控件区显示
    virtual void updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                      const QModelIndex &index) const override;
};

#endif // DATEDELEGATE_H
