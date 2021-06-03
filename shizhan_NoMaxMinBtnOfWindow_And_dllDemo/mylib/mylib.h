#ifndef MYLIB_H
#define MYLIB_H

//#include "mylib_global.h"

#include <QtCore/qglobal.h>

// Q_DECL_EXPORT:表示导出类
class Q_DECL_EXPORT Mylib
{
public:
    Mylib();
};

// Q_DECL_EXPORT:表示导出函数；extern "C"表示C语言方式导出，而非c++
extern "C" Q_DECL_EXPORT void testfun();
extern "C" Q_DECL_EXPORT char* testfun2();

#endif // MYLIB_H
