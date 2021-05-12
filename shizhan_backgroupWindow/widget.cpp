#include "widget.h"

#include <windows.h>
#include <QDebug>
#include <QDesktopWidget>
#include <QGuiApplication>


HWND FindDTWindow(){
    HWND hWnd = ::FindWindow(L"Progman", L"Program Manager");
    DWORD dResult = 0;

    SendMessageTimeout(hWnd,
        0x052C,
        0,
        NULL,
        SMTO_NORMAL,
        1000,
        &dResult);

    HWND hwndWorkW = NULL;
    do
    {
        hwndWorkW = ::FindWindowEx(NULL, hwndWorkW, L"WorkerW", NULL);
        if (NULL == hwndWorkW)
        {
            continue;
        }

        HWND hView = ::FindWindowEx(hwndWorkW, NULL, L"SHELLDLL_DefView", NULL);
        if (NULL == hView)
        {
            continue;
        }

        HWND h = ::FindWindowEx(NULL, hwndWorkW, L"WorkerW", NULL);
        while (NULL != h)
        {
            SendMessage(h, WM_CLOSE, 0, 0);
            h = ::FindWindowEx(NULL, hwndWorkW, L"WorkerW", NULL);
        }
        break;

    } while (true);

    return hWnd;

}
//————————————————
//版权声明：本文为CSDN博主「蓦然回首时已逝」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
//原文链接：https://blog.csdn.net/gorecording/article/details/88219422

static HWND g_workerw=0;
static BOOL CALLBACK EnumWndCallback(HWND tophandle,LPARAM topparamhandle){
    HWND p=FindWindowEx(tophandle,0,L"SHELLDLL_DefView",0);
    if(p!=0){
        //get the WorkerW window after the current one.
        g_workerw=FindWindowEx(0,tophandle,L"WorkerW",0);
    }
    return true;
}

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
#if 0
    HWND hwndProgram=FindWindowW(L"Progman",L"Program Manager");
        qDebug()<<"hwndProgram:"<<hwndProgram;
        DWORD dResult = 0;
    SendMessageTimeout(hwndProgram,0x052C,0,0,SMTO_NORMAL,1000,&dResult);
    EnumWindows(EnumWndCallback,0);
    ShowWindow(g_workerw,SW_HIDE);

    g_workerw=  FindDTWindow();
    //    HWND hwndFolderView=FindWindowW(L"SHELLDLL_DefView",NULL);
    //    qDebug()<<"hwndFolderView:"<<hwndFolderView;

    //    HWND hwndSelf =(HWND) this->winId();//本窗口的window handle

    //    SetParent(hwndSelf,hwndProgram);
    qDebug()<<"  g_workerw== "<<g_workerw;
    if(g_workerw==0){
            abort();
    }
#endif
    HWND promgramHandle= GetWorkerW();
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

    image=QImage("C:\\Users\\EDZ\\Desktop\\111.jpg");
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
        store.endPaint();
        store.flush(rect);
    }
    return QWindow::event(e);
}

