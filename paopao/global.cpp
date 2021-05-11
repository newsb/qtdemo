#include "global.h"

//地图map
//ATTR  map[ROW][COL]={};//全局变量初始化为0，（SPACE）  //类的成员不会初始化为0,必须手动赋值,


//ATTR attrAt(int row,int col){
//    if(row>=0&&row<=ROW-1&&col>=0&&col<=COL-1){
//        return map[row][col];
//    }
//    return UNDEFINE;
//}
//ATTR attrAt(QPoint pt)
//{
//    QPoint cAndr= coordinate2RowCol(pt);

//    int row=cAndr.y();
//    int col=cAndr.x();
//   ATTR attr= attrAt(row,col);
//   return attr;
//}

//void setBubbleAt(QPoint pt)
//{
//    QPoint cAndr= coordinate2RowCol(pt);

//    int row=cAndr.y();
//    int col=cAndr.x();
//    if (map[row][col]==SPACE){
//        map[row][col]=BUBBLE;
//    }
//}

//坐标 映射到行和列
QPoint coordinate2RowCol(QPoint coor){
//  return QPoint( qRound(1.0*  coor.x() /WALL_BRICK_SIZE),qRound(1.0*  coor.y() /WALL_BRICK_SIZE));
  return QPoint( coor.x() /WALL_BRICK_SIZE, coor.y() /WALL_BRICK_SIZE);
}

//行和列  映射到 坐标
QPoint rowCol2Coordinate(int r,int c){
    return QPoint( c*WALL_BRICK_SIZE,r*WALL_BRICK_SIZE);
}

//获取coor最近的格子
QPoint getNearestPoint(QPoint coor)
{
    QPoint rc= coordinate2RowCol(coor);
    return rowCol2Coordinate(rc.y(),rc.x());
}
