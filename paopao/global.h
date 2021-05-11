#ifndef GLOBAL_H
#define GLOBAL_H

#include <QRandomGenerator>


#define WIN_HEIGHT 600
#define WIN_WIDTH 1080
#define WALL_BRICK_SIZE 40
#define ROW (WIN_HEIGHT/WALL_BRICK_SIZE)
#define COL (WIN_WIDTH/WALL_BRICK_SIZE)

enum ATTR{
    SPACE,//空白
    WALL,//墙壁（不能炸）、
    BRICK,//砖块(可炸）
    BUBBLE,//炸弹
    UNDEFINE
};
//地图map
extern ATTR map[ROW][COL];//全局变量初始化为0，（SPACE）  //类的成员不会初始化为0,必须手动赋值


//extern struct pdesc const cameractrl_params[];
//            struct pdesc const cameractrl_params[] = {
//{PT_STRI_, 0,  1, OFFSET(cameractrl, homecmd), "homecmd", 32, 0, NULL, NULL},
//    {PT_STRI_, 0,  1, OFFSET(cameractrl, zoomctrl), "zoomctrl", 32, 0, NULL, NULL},
//    {PT_STRI_, 0,  1, OFFSET(cameractrl, focusctrl), "focusctrl", 32, 0, NULL, NULL},
//    {PT_STRI_, 0,  1, OFFSET(cameractrl, aperturectrl), "aperturectrl", 32, 0, NULL, NULL},
//    {PT_NULL_, 0,  0, 0, "", 0, 0, NULL, NULL} /* PT_NULL means tail of struct pdesc array */
//};

//返回map中元素类型
extern ATTR attrAt(int row,int col);
#include <QPoint>
extern ATTR attrAt(QPoint pt);


//坐标 映射到行和列
extern QPoint coordinate2RowCol(QPoint coor);
//行和列  映射到 坐标
extern QPoint rowCol2Coordinate(int r,int c);

extern void setBubbleAt(QPoint pt);

extern QPoint getNearestPoint(QPoint coor);


#endif // GLOBAL_H
