
#include "SelectWidget.h"
#include <QApplication>
#include <QDebug>
#include <windows.h>
#include <dbghelp.h>
//程式异常捕获
LONG ApplicationCrashHandler(EXCEPTION_POINTERS *pException)
{
    //创建 Dump 文件
    HANDLE hDumpFile = CreateFile(L"crash.dmp", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hDumpFile != INVALID_HANDLE_VALUE)
    {
        //Dump信息
    MINIDUMP_EXCEPTION_INFORMATION dumpInfo;
        dumpInfo.ExceptionPointers = pException;
        dumpInfo.ThreadId = GetCurrentThreadId();
        dumpInfo.ClientPointers = TRUE;

        //写入Dump文件内容
    MiniDumpWriteDump(GetCurrentProcess(), GetCurrentProcessId(), hDumpFile, MiniDumpNormal, &dumpInfo, NULL, NULL);
    }

    //这里弹出一个错误对话框并退出程序
//    MsgBox *msgbox = new MsgBox;
//    msgbox->setInfo(QObject::tr("Program crash"), QObject::tr("Express my sincere apologies for the mistake!"), QPixmap(":/msgbox/attention.png"), true, true);
//    msgbox->exec();
    qDebug() <<QObject::tr("Express my sincere apologies for the mistake!");

    return EXCEPTION_EXECUTE_HANDLER;
}


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);

  //  SetUnhandledExceptionFilter((LPTOP_LEVEL_EXCEPTION_FILTER)ApplicationCrashHandler);//注冊异常捕获函数


    SelectWidget sw;

    //    MyWidget w; // 2ren 版 ok

    //    SingleGame w; //单机+机器人  ok

    //    网络 + 2人
    //        bool bServer = false;
    //    QMessageBox::StandardButton ret = QMessageBox::question(nullptr, "server or client?", "作为服务器启动？");
    //    if (ret == QMessageBox::Yes) {
    //        bServer = true;
    //    }
    //    NetGame w(bServer);

    sw.show();
    return a.exec();
}
