#include "datatablewidget.h"
#include "ui_datatablewidget.h"
#include <QMouseEvent>
#include <QDragEnterEvent>

DataTableWidget::DataTableWidget(QWidget *parent)
    : QTableWidget(parent)
      , ui(new Ui::DataTableWidget)
{
    ui->setupUi(this);

    setAcceptDrops(true);
    setSelectionMode(ContiguousSelection);

    setColumnCount(3);
    setRowCount(5);
}

DataTableWidget::~DataTableWidget()
{
    delete ui;
}

void DataTableWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        startPos = event->pos();
    }
    QTableWidget::mousePressEvent(event);
}

void DataTableWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        int distance = (event->pos() - startPos).manhattanLength();
        if (distance >= QApplication::startDragDistance()) {
            performDrag();
        }
    }
}

void DataTableWidget::dragEnterEvent(QDragEnterEvent *event)
{
    DataTableWidget *source = qobject_cast<DataTableWidget *>(event->source());
    if (source && source != this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

void DataTableWidget::dragMoveEvent(QDragMoveEvent *event)
{
    DataTableWidget *source = qobject_cast<DataTableWidget *>(event->source());
    if (source && source != this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}
#include <QMimeData>
#include <QDrag>
/**
 *  首先我们获取选择的文本（selectionText()函数），如果为空则直接返回。
 * 然后创建一个QMimeData对象，设置了两个数据：HTML 格式和 CSV 格式。
 * 我们的 CSV 格式是以QByteArray形式存储的。
 * 之后我们创建了QDrag对象，将这个QMimeData作为拖动时所需要的数据，执行其exec()函数。
 * exec()函数指明，这里的拖动操作接受两种类型：复制和移动。当执行的是移动时，我们将已选区域清除。
 */
void DataTableWidget::performDrag()
{
    QString selectedString = selectionText();
    if (selectedString.isEmpty()) {
        return;
    }
    //    需要注意一点，QMimeData在创建时并没有提供 parent 属性，这意味着我们必须手动调用 delete 将其释放。
    //        但是，setMimeData()函数会将其所有权转移到QDrag名下，也就是会将其 parent 属性设置为这个QDrag。
    //    意味着，当QDrag被释放时，其名下的所有QMimeData对象都会被释放，所以结论是，
    //    我们实际是无需，也不能手动 delete 这个QMimeData对象。
    QMimeData *mimeData = new QMimeData;
    mimeData->setHtml(toHtml(selectedString));
    mimeData->setData("text/csv", toCsv(selectedString).toUtf8());

    QDrag *drag = new QDrag(this);
    drag->setMimeData(mimeData);
    if (drag->exec(Qt::CopyAction | Qt::MoveAction) == Qt::MoveAction) {
        selectionModel()->clearSelection();
    }
}
void DataTableWidget::dropEvent(QDropEvent *event)
{
    //如果是 CSV 类型，我们取出数据，转换成字符串形式，调用了fromCsv()函数生成新的数据项。
    if (event->mimeData()->hasFormat("text/csv")) {
        QByteArray csvData = event->mimeData()->data("text/csv");
        QString csvText = QString::fromUtf8(csvData);
        fromCsv(csvText);
        event->acceptProposedAction();
    }
}

QString DataTableWidget::selectionText() const
{
    QString selectionString;
    QString headerString;
    QAbstractItemModel *itemModel = model();
    QTableWidgetSelectionRange selection = selectedRanges().at(0);
    for (int row = selection.topRow(), firstRow = row;
         row <= selection.bottomRow(); row++) {
        for (int col = selection.leftColumn();
             col <= selection.rightColumn(); col++) {
            if (row == firstRow) {
                headerString.append(horizontalHeaderItem(col)->text()).append("\t");
            }
            QModelIndex index = itemModel->index(row, col);
            selectionString.append(index.data().toString()).append("\t");
        }
        selectionString = selectionString.trimmed();
        selectionString.append("\n");
    }
    return headerString.trimmed() + "\n" + selectionString.trimmed();
}

QString DataTableWidget::toHtml(const QString &plainText) const
{
#if QT_VERSION >= 0x050000
    QString result = plainText.toHtmlEscaped();
#else
    QString result = Qt::escape(plainText);
#endif
    result.replace("\t", "<td>");
    result.replace("\n", "\n<tr><td>");
    result.prepend("<table>\n<tr><td>");
    result.append("\n</table>");
    return result;
}

QString DataTableWidget::toCsv(const QString &plainText) const
{
    QString result = plainText;
    result.replace("\\", "\\\\");
    result.replace("\"", "\\\"");
    result.replace("\t", "\", \"");
    result.replace("\n", "\"\n\"");
    result.prepend("\"");
    result.append("\"");
    return result;
}

void DataTableWidget::fromCsv(const QString &csvText)
{
    QStringList rows = csvText.split("\n");
    QStringList headers = rows.at(0).split(", ");
    for (int h = 0; h < headers.size(); ++h) {
        QString header = headers.at(0);
        headers.replace(h, header.replace('"', ""));
    }
    setHorizontalHeaderLabels(headers);
    for (int r = 1; r < rows.size(); ++r) {
        QStringList row = rows.at(r).split(", ");
        setItem(r - 1, 0, new QTableWidgetItem(row.at(0).trimmed().replace('"', "")));
        setItem(r - 1, 1, new QTableWidgetItem(row.at(1).trimmed().replace('"', "")));
    }
}
