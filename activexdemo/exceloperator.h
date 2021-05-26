#ifndef EXCELOPERATOR_H
#define EXCELOPERATOR_H


#include <QObject>
#include <ActiveQt/QAxObject>
#include <QDebug>
#include <QDir>

class ExcelOperator : public QObject
{
    Q_OBJECT
public:
    explicit ExcelOperator(QObject *parent = nullptr);
    ~ExcelOperator();
    //打开文件
    bool open(QString path);
    //关闭文件
    bool close();
    //获取工作表数量
    int getSheetsCount();
    //根据名称创建工作表
    QAxObject* addSheet(QString name);
    //根据名称删除工作表
    bool delSheet(QString name);
    //根据编号删除工作表
    bool delSheet(int index);
    //根据名称获取工作表
    QAxObject* getSheet(QString name);
    //根据编号获取工作表
    QAxObject* getSheet(int index);
    //获取行对象
    QAxObject* getRows(QAxObject* pSheet);
    //获取行数
    int getRowsCount(QAxObject* pSheet);
    //获取列对象
    QAxObject* getColumns(QAxObject* pSheet);
    //获取列数
    int getColumnsCount(QAxObject* pSheet);
    //根据行列值获取单元格值, 如: 3行，5列
    QString getCell(QAxObject* pSheet, int row, int column);
    //根据行列编号获取单元格值, 如: "F6"
    QString getCell(QAxObject* pSheet, QString number);
    //根据行列值设置单元格值
    bool setCell(QAxObject* pSheet, int row, int column, QString value);
    //根据行列编号设置单元格值
    bool setCell(QAxObject* pSheet, QString number, QString value);


signals:

public slots:
private:
    QAxObject*      m_pExcel;
    QAxObject*      m_pWorksheets;
    QAxObject*      m_pWorkbook;
    QString         m_strPath;
};


#endif // EXCELOPERATOR_H
