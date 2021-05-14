#include "widget.h"

#include <windows.h>
#include <QDebug>
#include <QDesktopWidget>
#include <QGuiApplication>


HWND _workerw = nullptr;

inline BOOL CALLBACK EnumWindowsProc(_In_ HWND tophandle, _In_ LPARAM topparamhandle)
{
    HWND defview = FindWindowEx(tophandle, 0, L"SHELLDLL_DefView", nullptr);
    if (defview != nullptr)
    {
        _workerw = FindWindowEx(0, tophandle, L"WorkerW", 0);
    }
    return true;
}

HWND Widget::GetWorkerW(){
    int result;
    HWND windowHandle = FindWindow(L"Progman", nullptr);
    SendMessageTimeout(windowHandle, 0x052c, 0 ,0, SMTO_NORMAL, 0x3e8,(PDWORD_PTR)&result);
    EnumWindows(EnumWindowsProc,(LPARAM)nullptr);
    ShowWindow(_workerw,SW_HIDE);
    return windowHandle;
}



#include <QScreen>

Widget::Widget(QWindow *parent)
    : QWindow(parent),
      store(this)
{

    HWND promgramHandle= GetWorkerW();//win10 mingw-64获取为0，win7 自定义的壁纸获取为0
    qDebug()<<"  promgramHandle== "<<promgramHandle;
    if(promgramHandle==0){
            abort();
    }

    //获取桌面窗口
    QWindow *windowDesktop=QWindow::fromWinId((WId)promgramHandle);
    if(nullptr==windowDesktop){
        qDebug()<<"nullptr==windowDesktop";
        abort();
    }
    this->setParent(windowDesktop);

    QDesktopWidget w;
//    QRect rectFullDesktop =w.availableGeometry();
    QList<QScreen *> screens=QGuiApplication::screens();
    if(screens.count()<1){
        qDebug()<<"abort screens.count()<1";
        abort();
    }
    QRect rectFullDesktop =screens.first()->availableGeometry();
    this->setGeometry(rectFullDesktop);

    image=QImage(":/res/1.jpg");
}

Widget::~Widget()
{
}

#include <QPainter>
bool Widget::event(QEvent *e)
{
    if(e->type()==QEvent::Expose|| e->type()==QEvent::Resize){
        QRect rect(QPoint(0,0),this->size());
        store.resize(this->size());
        store.beginPaint(rect);
        QPainter painter(store.paintDevice());

        painter.fillRect(rect,Qt::white);
        painter.drawImage(0,0,image);
painter.end();

        store.flush(rect);
        store.endPaint();
    }
    return QWindow::event(e);
}

