#ifndef DATATABLEWIDGET_H
#define DATATABLEWIDGET_H

#include <QTableWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class DataTableWidget; }
QT_END_NAMESPACE
//表格继承自QTableWidget。虽然这是一个简化的QTableView
class DataTableWidget : public QTableWidget
{
    Q_OBJECT

public:
    DataTableWidget(QWidget *parent = nullptr);
    ~DataTableWidget();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void dragEnterEvent(QDragEnterEvent *event);
    void dragMoveEvent(QDragMoveEvent *event);
    void dropEvent(QDropEvent *event);
private:
    void performDrag();
    QString selectionText() const;

    QString toHtml(const QString &plainText) const;
    QString toCsv(const QString &plainText) const;
    void fromCsv(const QString &csvText);

    QPoint startPos;
private:
    Ui::DataTableWidget *ui;
};
#endif // DATATABLEWIDGET_H
