#ifndef MYSTONE_H
#define MYSTONE_H

#include <QString>
class MyStone {

  public:
    enum TYPE { CHE, MA, XIANG, SHI, JIANG, BING, PAO };
    MyStone();
    int _col, _row;
    bool _dead;
    int _id;
    bool _red;
    TYPE _type;

    void init(int id);
    QString getText()const;
    void rotate();
//    bool isSameColor(MyStone &stone)const;
};



#endif // MYSTONE_H
