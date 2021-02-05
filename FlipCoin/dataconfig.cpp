// clang-format off

#include "dataconfig.h"
#include <QDebug>

dataConfig::dataConfig(QObject *parent)
    : QObject(parent) {
    int array1[4][4] = {
{1, 1, 1, 1},
{1, 1, 0, 1},
{1, 0, 0, 0},
{1, 1, 0, 1}};
    insertData(1, array1);

    int array2[4][4] = {
{0, 0, 1, 1},
{0, 1, 0, 1},
{1, 0, 0, 0},
{1, 1, 0, 1}};
    insertData(2, array2);

    int array3[4][4] = {
{1, 0, 0, 0},
{0, 0, 0, 0},
{1, 0, 1, 0},
{1, 1, 0, 0}};
    insertData(3, array3);

    int array4[4][4]= {
{1, 0, 0, 0},
{0, 0, 0, 0},
{0, 0, 1, 0},
{0, 0, 0, 0}};
    insertData(4, array4);

    int array5[4][4]= {
{0, 0, 0, 0},
{0, 0, 0, 0},
{0, 0, 1, 0},
{0, 0, 0, 0}};
    insertData(5, array5);


    QVector<QVector<int>> v;
    // 设置种子
    srand((unsigned)time(NULL));
    // 4到19关随机生成
    for (int idx = 3; idx < 19; idx++) {
        v.clear();
        for (int i = 0; i < 4; i++) {
            QVector<int> v1;
            for (int j = 0; j < 4; j++) {
                int val = rand() % 2;
                if (val != 1 && val != 0) {
                    qDebug() << "val=" << val << ",set to 0!";
                    val = 0;
                }
                v1.push_back(val);
            }
            v.push_back(v1);
        }
        mData.insert(idx + 1, v);
    }

    // 20关设置全银币
    v.clear();
    for (int i = 0; i < 4; i++) {
        QVector<int> v1;
        for (int j = 0; j < 4; j++) {
            v1.push_back(0);
        }
        v.push_back(v1);
    }
    mData.insert(20, v);
}

void dataConfig::insertData(int level, int arr[4][4]) {
    QVector<QVector<int>> v;
    v.clear();
    for (int i = 0; i < 4; i++) {
        QVector<int> v1;
        for (int j = 0; j < 4; j++) {
            v1.push_back(arr[i][j]);
        }
        v.push_back(v1);
    }
    mData.insert(level, v);
}

// clang-format on
