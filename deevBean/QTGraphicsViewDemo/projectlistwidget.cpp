#include "projectlistwidget.h"
#include <QMouseEvent>
#include <QApplication>
#include <QMimeData>
#include <QDrag>

ProjectListWidget::ProjectListWidget(QWidget  *parent) : QListWidget(parent)
{
    //设置了setAcceptDrops()，使ProjectListWidget能够支持拖动操作
    setAcceptDrops(true);
}
/*
们检测鼠标左键点击，如果是的话就记录下当前位置。
需要注意的是，这个函数最后需要调用系统自带的处理函数，以便实现通常的那种操作。
这在一些重写事件的函数中都是需要注意的，前面我们已经反复强调过这一点。
*/
void ProjectListWidget::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
        startPos = event->pos();
    QListWidget::mousePressEvent(event);
}

void ProjectListWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton) {
        int distance = (event->pos() - startPos).manhattanLength();
        //判断，如果大于QApplication::startDragDistance()，我们才进行释放的操作。
        if (distance >= QApplication::startDragDistance())
            performDrag();
    }
    //调用系统默认的鼠标拖动函数
    //判断的意义在于，防止用户因为手的抖动等因素造成的鼠标拖动。
    //用户必须将鼠标拖动一段距离之后，我们才认为他是希望进行拖动操作，
    //而这一距离就是QApplication::startDragDistance()提供的，这个值通常是 4px。
    QListWidget::mouseMoveEvent(event);
}

void ProjectListWidget::dragEnterEvent(QDragEnterEvent *event)
{

}

void ProjectListWidget::performDrag()
{
    QListWidgetItem *item = currentItem();
    if (item) {
        //QDrag使用QMimeData存储数据
        QMimeData *mimeData = new QMimeData;
        mimeData->setText(item->text());

        QDrag *drag = new QDrag(this);
        drag->setMimeData(mimeData);
        //设置拖动发生时鼠标的样式。
        drag->setPixmap(QPixmap(":/images/person.png"));
        /*QDrag::exec()会阻塞拖动的操作，直到用户完成操作或者取消操作。
         * 它接受不同类型的动作作为参数，返回值是真正执行的动作。
         * 这些动作的类型一般为Qt::CopyAction，Qt::MoveAction和Qt::LinkAction。
         * 返回值会有这几种动作，同时还会有一个Qt::IgnoreAction用于表示用户取消了拖放。
         * 这些动作取决于拖放源对象允许的类型，目的对象接受的类型以及拖放时按下的键盘按键。
         * 在exec()调用之后，Qt 会在拖放对象不需要的时候释放掉。

        * */
        if (drag->exec(Qt::MoveAction) == Qt::MoveAction)
            delete item;
    }
}

void ProjectListWidget::dragMoveEvent(QDragMoveEvent *event)
{
    ProjectListWidget *source =   qobject_cast<ProjectListWidget *>(event->source());
    if (source && source != this) {
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}

void ProjectListWidget::dropEvent(QDropEvent *event)
{
    ProjectListWidget *source = qobject_cast<ProjectListWidget *>(event->source());
    if (source && source != this) {
        addItem(event->mimeData()->text());
        event->setDropAction(Qt::MoveAction);
        event->accept();
    }
}
