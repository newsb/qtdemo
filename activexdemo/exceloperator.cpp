#include "exceloperator.h"
#include <objbase.h>

ExcelOperator::ExcelOperator(QObject *parent) : QObject(parent)
  , m_pExcel(NULL)
  , m_pWorksheets(NULL)
  , m_pWorkbook(NULL)
{

}

ExcelOperator::~ExcelOperator()
{
    close();
}

bool ExcelOperator::open(QString path)
{
    m_strPath = path;
    QAxObject *pWorkbooks = NULL;
    CoInitializeEx(NULL, COINIT_MULTITHREADED);//多线程获取为NULL问题
    m_pExcel = new(std::nothrow) QAxObject();
    if (NULL == m_pExcel) {
        qCritical()<<"创建Excel对象失败...";
        return false;
    }
    try {
//        m_pExcel->setControl("Excel.Application");
        m_pExcel->setControl("KET.Application");
        m_pExcel->dynamicCall("SetVisible(bool)", false); //true 表示操作文件时可见，false表示为不可见
        m_pExcel->setProperty("DisplayAlerts", false);
        pWorkbooks = m_pExcel->querySubObject("WorkBooks");
        pWorkbooks->dynamicCall("Add");
        m_pWorkbook = m_pExcel->querySubObject("ActiveWorkBook");
        qDebug()<<"excel path: "<<m_strPath;

        // 获取打开的excel文件中所有的工作sheet
        m_pWorksheets = m_pWorkbook->querySubObject("WorkSheets");
    } catch (...) {
        qCritical()<<"打开文件失败...";
        return false;
    }

    return true;
}

bool ExcelOperator::close()
{
    qDebug()<<"excel close...";
    if (m_pExcel)
    {
        qDebug()<<"closing...";
        m_pWorkbook->dynamicCall("SaveAs(const QString&)", QDir::toNativeSeparators(m_strPath));
        m_pWorkbook->dynamicCall("Close()");
        m_pExcel->dynamicCall("Quit()");
        delete m_pExcel;
        m_pExcel = NULL;
    }
    return true;
}

int ExcelOperator::getSheetsCount()
{
    int count =  0;
    count = m_pWorksheets->property("Count").toInt();
    return count;
}


QAxObject* ExcelOperator::addSheet(QString name)
{
    QAxObject *pWorkSheet = NULL;
    try {
        int count = m_pWorksheets->property("Count").toInt();  //获取工作表数目
        QAxObject *pLastSheet = m_pWorksheets->querySubObject("Item(int)", count);
        pWorkSheet = m_pWorksheets->querySubObject("Add(QVariant)", pLastSheet->asVariant());
        pLastSheet->dynamicCall("Move(QVariant)", pWorkSheet->asVariant());
        pWorkSheet->setProperty("Name", name);  //设置工作表名称
    } catch (...) {
        qCritical()<<"创建sheet失败...";
    }
    return pWorkSheet;
}

bool ExcelOperator::delSheet(QString name)
{
    try {
        QAxObject *pFirstSheet = m_pWorksheets->querySubObject("Item(QString)", name);
        pFirstSheet->dynamicCall("delete");
    } catch (...) {
        qCritical()<<"删除sheet失败...";
        return false;
    }
    return true;
}

bool ExcelOperator::delSheet(int index)
{
    try {
        QAxObject *pFirstSheet = m_pWorksheets->querySubObject("Item(int)", index);
        pFirstSheet->dynamicCall("delete");
    } catch (...) {
        qCritical()<<"删除sheet失败...";
        return false;
    }
    return true;
}

QAxObject* ExcelOperator::getSheet(QString name)
{
    QAxObject* pWorkSheet = NULL;
    try {
        pWorkSheet = m_pWorksheets->querySubObject("Item(QString)", name);
    } catch (...) {
        qCritical()<<"获取sheet失败...";
    }
    return pWorkSheet;
}

QAxObject* ExcelOperator::getSheet(int index)
{
    QAxObject* pWorkSheet = NULL;
    try {
        pWorkSheet = m_pWorksheets->querySubObject("Item(int)", index);
    } catch (...) {
        qCritical()<<"获取sheet失败...";
    }
    return pWorkSheet;
}

QAxObject* ExcelOperator::getRows(QAxObject* pSheet)
{
    QAxObject* pRows = NULL;
    try {
        pRows = pSheet->querySubObject("Rows");
    } catch (...) {
        qCritical()<<"获取行失败...";
    }
    return pRows;
}

int ExcelOperator::getRowsCount(QAxObject* pSheet)
{
    int rows = 0;
    try {
        QAxObject* pRows = getRows(pSheet);
        rows = pRows->property("Count").toInt();
    } catch (...) {
        qCritical()<<"获取行数失败...";
    }
    return rows;
}

QAxObject* ExcelOperator::getColumns(QAxObject* pSheet)
{
    QAxObject* pColumns = NULL;
    try {
        pColumns = pSheet->querySubObject("Columns");
    } catch (...) {
        qCritical()<<"获取列失败...";
    }
    return pColumns;
}

int ExcelOperator::getColumnsCount(QAxObject* pSheet)
{
    int columns = 0;
    try {
        QAxObject* pColumns = getColumns(pSheet);
        columns = pColumns->property("Count").toInt();
    } catch (...) {
        qCritical()<<"获取列数失败...";
    }
    return columns;
}

QString ExcelOperator::getCell(QAxObject* pSheet, int row, int column)
{
    QString strCell = "";
    try {
        QAxObject* pCell = pSheet->querySubObject("Cells(int, int)", row, column);
        strCell = pCell->property("Value").toString();
    } catch (...) {
        qCritical()<<"获取单元格信息失败...";
    }

    return strCell;
}

QString ExcelOperator::getCell(QAxObject* pSheet, QString number)
{
    QString strCell = "";
    try {
        QAxObject* pCell = pSheet->querySubObject("Range(QString)", number);
        strCell = pCell->property("Value").toString();
    } catch (...) {
        qCritical()<<"获取单元格信息失败...";
    }

    return strCell;
}

bool ExcelOperator::setCell(QAxObject* pSheet, int row, int column, QString value)
{
    try {
        QAxObject* pCell = pSheet->querySubObject("Cells(int, int)", row, column);
        pCell->setProperty("Value", value);
    } catch (...) {
        qCritical()<<"写入单元格信息失败...";
        return false;
    }
    return true;
}

bool ExcelOperator::setCell(QAxObject* pSheet, QString number, QString value)
{
    try {
        QAxObject* pCell = pSheet->querySubObject("Range(QString)", number);
        pCell->setProperty("Value", value);
    } catch (...) {
        qCritical()<<"写入单元格信息失败...";
        return false;
    }
    return true;
}
