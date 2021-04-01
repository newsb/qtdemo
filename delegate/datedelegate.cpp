#include "datedelegate.h"
#include <QDateTimeEdit>

DateDelegate::DateDelegate(QObject *parent)
    : QItemDelegate(parent) {}

QWidget *DateDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option,
                                    const QModelIndex &index) const {
    QDateTimeEdit *editor = new QDateTimeEdit(parent);
    editor->setDisplayFormat("yyyy-MM-dd");
    editor->setCalendarPopup(true);
    //安装事件过滤器，让DateDelegate能捕获QDateTimeEdit对象的事件
    editor->installEventFilter(const_cast<DateDelegate *>(this));
    return editor;
}

void DateDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const {
    //获取指定index数据项的数据。
    //调用QModelIndex的model()函数可获得提供index的Model对象。
    QString dateStr = index.model()->data(index).toString();
    QDate date = QDate::fromString(dateStr, Qt::ISODate);
    //将editor转换为QDateTimeEdit对象，以获得编辑控件的指针。
    QDateTimeEdit *edit = static_cast<QDateTimeEdit *>(editor);
    //设置控件的显示数据
    edit->setDate(date);
}

void DateDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const {
    //通过紧缩转换获取编辑控件的对象指针
    QDateTimeEdit *edit = static_cast<QDateTimeEdit *>(editor);
    //获取编辑控件中的数据更新
    QDate date = edit->date();
    //将数据修改更新到model中。
    model->setData(index, QVariant(date.toString(Qt::ISODate)));
}

void DateDelegate::updateEditorGeometry(QWidget *editor, const QStyleOptionViewItem &option,
                                        const QModelIndex &index) const {
    editor->setGeometry(option.rect);
}
