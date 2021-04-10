#include "mystone.h"

MyStone::MyStone() {}

void MyStone::init(int id) {
    struct {
        int row, col;
        MyStone::TYPE type;
    } pos[16] = {
     {0,0,MyStone::CHE},{0,1,MyStone::MA},{0,2,MyStone::XIANG},{0,3,MyStone::SHI},{0,4,MyStone::JIANG},
     {0, 5, MyStone::SHI},{0, 6, MyStone::XIANG}, {0, 7, MyStone::MA},    {0, 8, MyStone::CHE},
    //pao=9,10
     {2, 1, MyStone::PAO},   {2, 7, MyStone::PAO},

     {3, 0, MyStone::BING},  {3, 2, MyStone::BING},  {3, 4, MyStone::BING},
     {3, 6, MyStone::BING},  {3, 8, MyStone::BING}};

    _id = id;
    _dead = false;
    _red = id < 16;

    if (id < 16) {
        _row = pos[id].row;
        _col = pos[id].col;
        _type = pos[id].type;
    } else {
        _row = 9 - pos[id - 16].row;
        _col = 8 - pos[id - 16].col;
        _type = pos[id - 16].type;
    }
}

QString MyStone::getText()const {
    switch (_type) {
        case CHE:
            return "車";
        case MA:
            return "馬";

        case XIANG:
            if (_red) {
                return "相";
            } else {
                return "象";
            }
        case SHI:
            if (_red) {
                return "仕";
            } else {
                return "士";
            }
        case JIANG:

            if (_red) {
                return "帅";
            } else {
                return "将";
            }
        case BING:
            if (_red) {
                return "兵";
            } else {
                return "卒";
            }
        case PAO:
            if (_red) {
                return "砲";
            } else {
                return "炮";
            }
        default:
            return "null";
    }
}
void MyStone::rotate() {
    this->_col = 8 - this->_col;
    this->_row = 9 - this->_row;
}

