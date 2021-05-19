QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++11

# The following define makes your compiler emit warnings if you use
# any Qt feature that has been marked deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if it uses deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

SOURCES += \
    main.cpp \
    dialog.cpp \
    mainwindow.cpp \
    mywidget.cpp

HEADERS += \
    dialog.h \
    mainwindow.h \
    mywidget.h

FORMS += \
    dialog.ui

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

#LIBS :指定工程里需要链接的库文件（.lib或.dll）。
#-L指定库文件路径，-l指定库文件名（）
#不指定库文件路径时，需要将库文件复制到项目路径（D:\qtGit2\NoMaxMinBtnOfWindowDemo1\）或输出的debug路径（D:\qtGit2\NoMaxMinBtnOfWindowDemo1\debug）
#LIBS += -L -lmylib
# $$PWD ：当前目录(当前.pro文件所在的路径。)，相当于.
# $$OUT_PWD :表示输出的“Makefile”所在的路径（通常在编译后生成的.exe文件的上层目录里）。
LIBS += -L$$PWD/mylib/debug/ -lmylib

#列出工程中 #include 项需要搜索的路径，即头文件的路径。 多个路径用空格隔开。 如果路径本身包含空格，则需要用双引号引起来。
#INCLUDEPATH +=D:\qtGit2\NoMaxMinBtnOfWindowDemo1\mylib D:\desktop2021-01-15



