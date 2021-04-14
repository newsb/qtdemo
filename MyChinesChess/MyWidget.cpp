#include "MyWidget.h"
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QtMath>
#include <QFileDialog>
/**TODO :  将军的时候，特殊语音提示；
        将军的时候，不允许动其他棋子
        加载残棋

 * */
MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent) {

    resize(600, 600);
    bMouseOnBtn=false;
    bMouseOnBtn1=false;
    mUseTime=0;
    mLastSelectIdRed=-1;
    mLastSelectIdBlack=-1;
    // 所以想要实现mouseMoveEvent,若是setMouseTrack(true),直接可以得到监听事件。若是setMouseTrack(false),只有鼠标按下才会有mouseMove监听事件响应。
    setMouseTracking(true);
    //隐藏form标题栏
    // setWindowFlags(Qt::FramelessWindowHint);

    //    for (int i = 0; i < 32; ++i) {
    //        _s[i].init(i);
    //   }
    init(true);

#if 0
//    for (int i = 0; i < 32; ++i) {
//        if(_s[i]._red&&_s[i]._type==MyStone::BING){
//           _s[i]._col
//        }

        //if (i != 20 && i != 5) _s[i]._dead = true;
//    }
    //13=红兵，中心的
    _s[13]._col=4;
    _s[13]._row=1;

//    _s[13 ]._dead=true;
    _s[13+16]._dead=true;

//    _s[9+16]._col=4;

    //马
//    _s[1+16]._col=2;
//    _s[1+16]._row=2;

#endif

    mPassSteps.clear();

    connect(this,&MyWidget::repentance_signal,&MyWidget::repentanceStep);

    mUseTimeId=startTimer(1000);

    bells=new QSound(":/res/bell.wav");

     bells2 = new QMediaPlayer;

    bells2->setMedia(QUrl(":/res/jiangjun.mp3"));
    bells2->setVolume(50);
//    bells2->play();

}

void MyWidget::timerEvent(QTimerEvent *event)
{
    if(mUseTimeId==event->timerId()){
        //游戏结束了，不继续计时
        if (m_winner != 0) {
            killTimer(mUseTimeId);
        }
        mUseTime++;
        update(mUseTimeRect);
    }
}
void MyWidget::init(bool bRedSide) {
    for (int i = 0; i < 32; ++i) {
        _s[i].init(i);

        if( _s[i]._type==MyStone::JIANG){
            if(i<16){
                redJIANGId= _s[i]._id;//保存老将的id，以后使用时不用遍历
            }
            else{
                blackJIANGId= _s[i]._id;
            }
        }
    }
    if (bRedSide) {
        for (int i = 0; i < 32; ++i) {
            _s[i].rotate();
        }
    }
    _bRedSide = bRedSide;
    selectId = -1;
    bTranRed = true;

    update();
}

void MyWidget::repentanceStep(int backCount){
    while (backCount>0){
        if(mPassSteps.isEmpty() ) return ;
        Step *step = mPassSteps.back();
        unfakeMove(step);
        mUseTime=0 ;
        update();
        qDebug()<<"悔棋。"<<_s[step->_moveid].getText() <<"fromcol:"<<step->_colFrom<<" fromrow:"<<step->_rowFrom  <<"tocol:"<<step->_colTo<<" torow:"<<step->_rowTo;
        mPassSteps.pop_back();//mPassSteps.removeLast();
        delete step;
        backCount--;
    }
}

MyWidget::~MyWidget() {}

void MyWidget::paintEvent(QPaintEvent *) {

    QPainter p(this);

    //棋盘背景图
//    QPixmap pix(":/res/bg.jpg");
//    pix=pix.scaled(this->width(),this->height());
//    p.drawPixmap(0,0,pix);

    drawBoard(p);

    //绘制棋子
    p.save();
    for (int i = 0; i < 32; ++i) {
        drawStone(p, i);
    }
    p.restore();
    //绘制输赢结果。
    drawGameResult(p);
    //绘制操作按钮
    drawGameBtns(p);
}

void MyWidget::drawGameBtns(QPainter &p ){
    p.save();

    if(bMouseOnBtn1){
        p.setBrush(QBrush(Qt::white));
    }else{
        p.setBrush(Qt::BrushStyle::NoBrush);
    }

    p.setPen(Qt::blue);
    p.drawEllipse(mBackRect);//p.drawRect(mBackRect);
    p.setFont(QFont("微软雅黑", 16, 700));
    p.drawText(mBackRect, "返回", QTextOption(Qt::AlignCenter));

    if(bMouseOnBtn  ){
        p.setBrush(QBrush(Qt::darkCyan));
    }else{
        p.setBrush(Qt::BrushStyle::NoBrush);
    }

    p.drawRect(mRepentanceRect);
//    p.setFont(QFont("微软雅黑", 16, 700));
    p.drawText(mRepentanceRect, "悔棋", QTextOption(Qt::AlignCenter));

    if(  bMouseOnSave){
        p.setBrush(QBrush(Qt::darkCyan));
    }else{
        p.setBrush(Qt::BrushStyle::NoBrush);
    }

    p.drawRect(mSaveRect);
    p.drawText(mSaveRect, "保存", QTextOption(Qt::AlignCenter));

    if( bMouseOnLoad ){
        p.setBrush(QBrush(Qt::darkCyan));
    }else{
        p.setBrush(Qt::BrushStyle::NoBrush);
    }
    p.drawRect(mLoadRect);
    p.drawText(mLoadRect, "加载", QTextOption(Qt::AlignCenter));

    p.setBrush(Qt::BrushStyle::NoBrush);
    p.drawEllipse(mUseTimeRect);
//    p.setFont(QFont("微软雅黑", 16, 700));
    p.drawText(mUseTimeRect,QString("%1 s").arg(mUseTime), QTextOption(Qt::AlignCenter));

    p.restore();
}

void MyWidget::resizeEvent(QResizeEvent *)
{
//    event->size();

    double colw =1.0* (this->width() - PADDING_LEFT - PADDING_RIGHT) / (COL_COUNT + 2);
    double rowh = 1.0*(this->height() - PADDING_TOP - PADDING_BOTTOM) / (ROW_COUNT + 2);
    mColumnWidth = colw;
    mRowHeight = rowh;
    _r = colw < rowh ? colw / 2 : rowh / 2;


    mBackRect=QRect(this->width()-PADDING_RIGHT+10,PADDING_TOP+50,
                      PADDING_RIGHT-20,25);
    mRepentanceRect=QRect(this->width()-PADDING_RIGHT+10,mBackRect.bottom()+20,
                            PADDING_RIGHT-20,25);

    mSaveRect=QRect(this->width()-PADDING_RIGHT+10,mRepentanceRect.bottom()+20,
                      PADDING_RIGHT-20,25);
    mLoadRect=QRect(this->width()-PADDING_RIGHT+10,mSaveRect.bottom()+20,
                      PADDING_RIGHT-20,25);

    mUseTimeRect=QRect(this->width()-PADDING_RIGHT+10,this->height()-PADDING_BOTTOM-55,
                         PADDING_RIGHT-20,35);
}
void MyWidget::drawGameResult(QPainter &p){
    if (m_winner == 1 || m_winner == 2) {
        p.save();
        QRect rect(PADDING_LEFT + mColumnWidth * 3, PADDING_TOP + mRowHeight * 5,  mColumnWidth * 4,  mRowHeight);
        p.setPen(Qt::red);
        p.setFont(QFont("微软雅黑",14,16,true));
        p.drawText(rect, m_winner == 1 ?"你赢了":"你输了", QTextOption(Qt::AlignCenter));
        p.restore();
    }
}

void MyWidget::mouseMoveEvent(QMouseEvent *event)
{
    bMouseOnBtn=(mRepentanceRect.contains( event->pos()));
    update(mRepentanceRect);
    bMouseOnBtn1=(mBackRect.contains( event->pos()));
    update(mBackRect);
    bMouseOnSave=mSaveRect.contains(event->pos());
    update(mSaveRect);
    bMouseOnLoad=mLoadRect.contains(event->pos());
    update(mLoadRect);
}
QPainterPath MyWidget::getPaoBingPostionPath(QPoint &point, int half) const {
    QPainterPath path;
    if (half == 0 || half == 1) {
        //左上
        path.moveTo(point.x() - 20, point.y() - 5);
        path.lineTo(point.x() - 5, point.y() - 5);
        path.lineTo(point.x() - 5, point.y() - 20);
    }

    if (half == 0 || half == 2) {
        //右上
        path.moveTo(point.x() + 5, point.y() - 20);
        path.lineTo(point.x() + 5, point.y() - 5);
        path.lineTo(point.x() + 20, point.y() - 5);
    }
    if (half == 0 || half == 1) {
        //左下
        path.moveTo(point.x() - 20, point.y() + 5);
        path.lineTo(point.x() - 5, point.y() + 5);
        path.lineTo(point.x() - 5, point.y() + 20);
    }

    if (half == 0 || half == 2) {
        //右下
        path.moveTo(point.x() + 20, point.y() + 5);
        path.lineTo(point.x() + 5, point.y() + 5);
        path.lineTo(point.x() + 5, point.y() + 20);
    }
    return path;
}

bool MyWidget::isBottomSide(int id) { return _bRedSide == _s[id]._red; }

void MyWidget::drawStone(QPainter &painter, int id) {
    if (_s[id]._dead) return;

    QPointF c = center(id);
    QRect rect = QRect(c.x() - _r, c.y() - _r, 2 * _r, 2 * _r);

    //绘制上次选择的棋子边框
    QBrush oldB=painter.brush();
//    painter.setBrush(QBrush(Qt::magenta));
    painter.setBrush(Qt::NoBrush);
    painter.setPen(QPen(QBrush(Qt::magenta),3) );
    QRectF rect2 = QRectF(c.x() - _r-5, c.y() - _r-5, 2 * _r+10, 2 * _r+10);

//            QRect rect3(rect2.left(),
//                        rect2.top(),
//                        rect2.width()+20,
//                        rect2.height()+20 );
    if(mLastSelectIdRed==id || mLastSelectIdBlack==id){
//        painter.drawRect(rect2);
        QPainterPath path;
//        int spanRad=60;
//        int dRad=(90-spanRad)/2;

        int dr1=_r-10;
        path.moveTo(rect2.left(), rect2.top());
        path.lineTo(rect2.left(), rect2.top()+dr1);
        path.moveTo(rect2.left(), rect2.top());
        path.lineTo(rect2.left()+dr1, rect2.top());
//        rect3.setLeft(rect2.left()-20);
//        rect3.setTop(rect2.top()-20);
//        path.arcTo(rect3 , 90+dRad,spanRad);

        path.moveTo(rect2.right()-dr1, rect2.top());
        path.lineTo(rect2.right() , rect2.top());
        path.lineTo(rect2.right(), rect2.top()+dr1);

//        rect3.setLeft(rect2.left()+20);
//        rect3.setTop(rect2.top());
//        path.arcTo(rect3,0+dRad,spanRad);

        path.moveTo(rect2.left(), rect2.bottom()-dr1);
        path.lineTo(rect2.left() ,rect2.bottom());
        path.lineTo(rect2.left()+dr1 ,rect2.bottom());
        path.moveTo(rect2.left(), rect2.bottom()-dr1);

//        rect3.setTop(rect2.top()-20);
//        rect3.setLeft(rect2.left());
//        path.arcTo(rect3,180+dRad,spanRad);

        path.moveTo(rect2.right()-dr1, rect2.bottom() );
        path.lineTo(rect2.right() ,rect2.bottom());
        path.lineTo(rect2.right() ,rect2.bottom()-dr1);
        path.moveTo(rect2.right()-dr1, rect2.bottom() );

//        rect3.setTop(rect2.top()-20);
//        rect3.setLeft(rect2.left()-20);
//        path.arcTo(rect2,270+dRad,spanRad);

//        painter.setPen(Qt::darkBlue);
        painter.drawPath(path);
    }
    painter.setBrush(oldB);

#if 1
    if (selectId == id) {
        painter.setBrush(QBrush(Qt::white));
    } else {
        painter.setBrush(QBrush(Qt::lightGray));
    }
    painter.setPen(Qt::darkYellow);
    painter.drawEllipse(c, _r , _r );

    painter.setPen(Qt::darkYellow);
    painter.drawEllipse(c, _r-5, _r-5);



    painter.setPen(Qt::black);
    if (_s[id]._red) {
        painter.setPen(Qt::red);
    }
    //painter.drawEllipse(c, _r - 5, _r - 5);
    painter.setFont(QFont("微软雅黑", _r, 700));
    painter.drawText(rect, _s[id].getText(), QTextOption(Qt::AlignCenter));
#endif

}
//const int D_COL_W=3;
//const int D_ROW_H=10;
//3d效果：从上到下     行高递增、，列宽递增
void MyWidget::drawBoard(QPainter &p) {
    double colw = mColumnWidth;
    double rowh = mRowHeight;
    p.setRenderHint(QPainter::Antialiasing); //抗锯齿
    QPen pen = QPen(QColor(Qt::darkCyan));
    pen.setWidth(5);
    p.setPen(pen);



    //竖线
    for (int i = 0; i <= COL_COUNT; i++) {
        if (i != COL_COUNT && i != 0) {
            QPointF pff(PADDING_LEFT + colw * (1 + i), PADDING_TOP + rowh);
            QPointF pft(PADDING_LEFT + colw * (1 + i), ((COL_COUNT / 2) + 1) * rowh +PADDING_TOP);
            p.drawLine(pff, pft);

            pff.setX(PADDING_LEFT + colw * (1 + i));
            pff.setY(PADDING_TOP + ((COL_COUNT / 2) + 2) * rowh);
            pft.setX(PADDING_LEFT + colw * (1 + i));
            pft.setY(height() - rowh - PADDING_BOTTOM);
            p.drawLine(pff,pft );

        } else {
            QPointF pff(PADDING_LEFT + colw * (1 + i), rowh + PADDING_TOP);
            QPointF pft(PADDING_LEFT + colw * (1 + i), height() - rowh - PADDING_BOTTOM);
            p.drawLine(pff,pft);
        }
    }
    //    pen.setColor(QColor(Qt::red));
    //    p.setPen(pen);
    //横线
    for (int i = 0; i <= ROW_COUNT; i++) {
        QPointF pff(colw+PADDING_LEFT, rowh * (1 + i) +PADDING_TOP);
        QPointF pft(width() - colw - PADDING_RIGHT, rowh * (1 + i)+ PADDING_TOP);
        p.drawLine(pff,pft) ;
    }
    //九宫格
    QPointF pff(PADDING_LEFT + colw * 4, PADDING_TOP + rowh);
    QPointF pft(PADDING_LEFT + 6 * colw, PADDING_TOP + rowh * 3);
    p.drawLine(pff,pft );

     pff=QPointF(PADDING_LEFT + colw * 6, PADDING_TOP + rowh);
     pft=QPointF(PADDING_LEFT + colw * 4, PADDING_TOP + 3 * rowh);
    p.drawLine(pff,pft );

    pff=QPointF(PADDING_LEFT + colw * 4, PADDING_TOP + rowh * 10);
    pft=QPointF(PADDING_LEFT + 6 * colw, PADDING_TOP + rowh * 8);
    p.drawLine(pff,pft );

    pff=QPointF(PADDING_LEFT + colw * 6, PADDING_TOP + rowh * 10);
    pft=QPointF(PADDING_LEFT + colw * 4, PADDING_TOP + 8 * rowh);
    p.drawLine(pff,pft);
    //炮 位置
    p.save();
    pen.setWidth(3);
    p.setPen(pen);
    QPoint pt = QPoint(PADDING_LEFT + colw * 2, PADDING_TOP + rowh * 3);
    QPainterPath path = this->getPaoBingPostionPath(pt);
    p.drawPath(path);

    pt.setX(PADDING_LEFT + colw * 8);
    path = this->getPaoBingPostionPath(pt);
    p.drawPath(path);

    pt.setY(PADDING_TOP + rowh * 8);
    path = this->getPaoBingPostionPath(pt);
    p.drawPath(path);

    pt.setX(PADDING_LEFT + colw * 2);
    path = this->getPaoBingPostionPath(pt);
    p.drawPath(path);
    //上部 兵位置
    pt.setX(PADDING_LEFT + colw);
    pt.setY(PADDING_TOP + rowh * 4);
    path = this->getPaoBingPostionPath(pt, 2);
    p.drawPath(path);
    pt.setX(PADDING_LEFT + colw * 3);
    path = this->getPaoBingPostionPath(pt);
    p.drawPath(path);
    pt.setX(PADDING_LEFT + colw * 5);
    path = this->getPaoBingPostionPath(pt);
    p.drawPath(path);
    pt.setX(PADDING_LEFT + colw * 7);
    path = this->getPaoBingPostionPath(pt);
    p.drawPath(path);
    pt.setX(PADDING_LEFT + colw * 9);
    path = this->getPaoBingPostionPath(pt, 1);
    p.drawPath(path);
    //下部 兵位置
    pt.setX(PADDING_LEFT + colw);
    pt.setY(PADDING_TOP + rowh * 7);
    path = this->getPaoBingPostionPath(pt, 2);
    p.drawPath(path);
    pt.setX(PADDING_LEFT + colw * 3);
    path = this->getPaoBingPostionPath(pt);
    p.drawPath(path);
    pt.setX(PADDING_LEFT + colw * 5);
    path = this->getPaoBingPostionPath(pt);
    p.drawPath(path);
    pt.setX(PADDING_LEFT + colw * 7);
    path = this->getPaoBingPostionPath(pt);
    p.drawPath(path);
    pt.setX(PADDING_LEFT + colw * 9);
    path = this->getPaoBingPostionPath(pt, 1);
    p.drawPath(path);

    p.restore();
    QRect rect = QRect(PADDING_LEFT + colw * 1, PADDING_TOP + rowh * 5, colw * 3, rowh);
    p.setFont(QFont("微软雅黑", 24));
    p.setPen(Qt::darkYellow);

    QRect rect2 = QRect(PADDING_LEFT + colw * 6, PADDING_TOP + rowh * 5, colw * 3, rowh);

    QTransform transform;
    //对弈双方的棋盘上绘制不一样的【楚河汉界】
    if(_bRedSide){
        p.drawText(rect, "楚河", QTextOption(Qt::AlignCenter));
        //    p.drawRect(rect)    ;

         p.save();
         transform.translate(rect2.left()+rect2.width()/2, rect2.top()+rect2.height()/2);
         transform.rotate(180);
         p.setTransform(transform);
//         p.drawRect(QRect( -rect2.width()/2,-rect2.height()/2,rect2.width(),rect2.height()))  ;
         p.drawText(QRect(-rect2.width()/2,-rect2.height()/2,rect2.width(),rect2.height()), "汉界", QTextOption(Qt::AlignCenter));
         p.restore();
    }else{
        p.save();
        transform.translate(rect.left()+rect.width()/2, rect.top()+rect.height()/2);
        transform.rotate(180);
        p.setTransform(transform);
        p.drawText(QRect( -rect.width()/2,-rect.height()/2,rect.width(),rect.height()), "楚河", QTextOption(Qt::AlignCenter));
        p.restore();

        p.drawText(rect2, "汉界", QTextOption(Qt::AlignCenter));
    }

}

QPointF MyWidget::center(int id) {
    return QPointF(PADDING_LEFT + (_s[id]._col + 1) * mColumnWidth, PADDING_TOP + (_s[id]._row + 1) * mRowHeight);
}

bool MyWidget::getColRow(QPoint pt, int &col, int &row) {
    double d = 1.0 * (pt.x() - PADDING_LEFT) / mColumnWidth;
    col = qRound(d) - 1;
    d = 1.0 * (pt.y() - PADDING_TOP) / mRowHeight;
    row = qRound(d) - 1;
    //    qDebug() << "d=" << d << ";col=" << col << ";row=" << row;
    return true;
}
//没有空对象!!!
MyStone *MyWidget::getStoneAt(int col, int row) {
    //
    for (int i = 0; i < 32; i++) {
        if (_s[i]._col == col && _s[i]._row == row && !_s[i]._dead) {
            return &_s[i];
            break;
        }
    }
    return nullptr;
}

int MyWidget::getStoneIdAt(int col, int row) {

    MyStone *p = getStoneAt(col, row);

    if (p != nullptr) {
        return p->_id;
    }
    return -1;
}

bool MyWidget::canMove(int moveId, int col, int row, int killId) {
    if (col < 0 || col > COL_COUNT || row < 0 || row > ROW_COUNT) return false;
    if (killId != -1) {
        if (_s[moveId]._red == _s[killId]._red) {
            //换选中
            selectId = killId;
            update();
            return false;
        }
    }
    //  不用考虑目标位置是自己的棋子，这种情况已经过滤了
    switch (_s[moveId]._type) {
        case MyStone::CHE:
            return canMoveCHE(moveId, col, row, killId);
            break;
        case MyStone::MA:
            return canMoveMA(moveId, col, row, killId);
            break;
        case MyStone::PAO:
            return canMovePAO(moveId, col, row, killId);
            break;
        case MyStone::XIANG:
            return canMoveXIANG(moveId, col, row, killId);
            break;
        case MyStone::SHI:
            return canMoveSHI(moveId, col, row, killId);
            break;
        case MyStone::JIANG:
            return canMoveJIANG(moveId, col, row, killId);
            break;
        case MyStone::BING:
            return canMoveBING(moveId, col, row, killId);
            break;
    }
    return false;
}

bool MyWidget::canMoveMA(int moveId, int col, int row, int) {

    int dr = _s[moveId]._row - row;
    int dc = _s[moveId]._col - col;
    int d = abs(dr) * 10 + abs(dc);
    // qDebug() << "dr= " << dr << ",dc=" << dc << ",d=" << d;

    if (d == 12) {    // row=1,col=2 曰字，
        if (dc > 0) { //往左的曰字，判断左面一个位置有没有棋子，
            MyStone *p = getStoneAt(_s[moveId]._col - 1, _s[moveId]._row);
            return p == nullptr;
        } else { //往右的日字，判断右面一个位置有没有棋子，
            MyStone *p = getStoneAt(_s[moveId]._col + 1, _s[moveId]._row);
            return p == nullptr;
        }
    } else if (d == 21) { // row=2,col=1 日字
        if (dr > 0) {     //往上的日字，判断上面一个位置有没有棋子，
            MyStone *p = getStoneAt(_s[moveId]._col, _s[moveId]._row - 1);
            return p == nullptr; //上面有棋子，bietui

        } else { //往下的日字，判断下面一个位置有没有棋子，
            MyStone *p = getStoneAt(_s[moveId]._col, _s[moveId]._row + 1);
            return p == nullptr; // 下面有棋子，bietui
        }
    }

    return false;
}
bool MyWidget::canMoveXIANG(int moveId, int col, int row, int) {
    int dr = _s[moveId]._row - row;
    int dc = _s[moveId]._col - col;
    int d = abs(dr) * 10 + abs(dc);
    //  相不能过河
    if (!isBottomSide(moveId)) { //_s[moveId]._red
        if (row > 5) return false;
    } else {
        if (row < 5) return false;
    }
    // qDebug() << "dr= " << dr << ",dc=" << dc << ",d=" << d;
    if (d == 22) {              // row=2,col=2 田字，
        if (dc > 0 && dr > 0) { // 左上
            MyStone *p = getStoneAt(_s[moveId]._col - 1, _s[moveId]._row - 1);
            return p == nullptr;
        } else if (dc > 0 && dr < 0) { // 左下
            MyStone *p = getStoneAt(_s[moveId]._col - 1, _s[moveId]._row + 1);
            return p == nullptr;
        } else if (dc < 0 && dr < 0) { // you下
            MyStone *p = getStoneAt(_s[moveId]._col + 1, _s[moveId]._row + 1);
            return p == nullptr;
        } else if (dc < 0 && dr > 0) { // 右上
            MyStone *p = getStoneAt(_s[moveId]._col + 1, _s[moveId]._row - 1);
            return p == nullptr;
        }
    }
    return false;
}
bool MyWidget::canMoveSHI(int moveId, int col, int row, int) {
    //九宫格范围
    if (isBottomSide(moveId)) { //_s[moveId]._red) {
        if (row < 7) return false;
    } else {
        if (row > 2) return false;
    }
    if (col < 3) return false;
    if (col > 5) return false;

    int dr = _s[moveId]._row - row;
    int dc = _s[moveId]._col - col;
    int d = abs(dr) * 10 + abs(dc); // 12、21（马） 22(相） 10、1（将、兵）
    //走斜线
    return d == 11;
}
bool MyWidget::canMoveJIANG(int moveId, int col, int row, int killId) {
    if (killId != -1 && _s[killId]._type == MyStone::JIANG) {
        return canMoveCHE(moveId, col, row, killId);
    }
    //九宫格范围
    if (isBottomSide(moveId)) { // _s[moveId]._red
        if (row < 7) return false;
    } else {
        if (row > 2) return false;
    }
    if (col < 3) return false;
    if (col > 5) return false;

    int dr = _s[moveId]._row - row;
    int dc = _s[moveId]._col - col;
    int d = abs(dr) * 10 + abs(dc);
    //步长为1
    return d == 1 || d == 10;
}
bool MyWidget::canMovePAO(int moveId, int col, int row, int killId) {

    int dr = _s[moveId]._row - row;
    int dc = _s[moveId]._col - col;
    int c = -1;
    if (abs(dr) == 0 && abs(dc) != 0) {
        c = countStoneAtCol(row, _s[moveId]._col, col);
    } else if (abs(dr) != 0 && abs(dc) == 0) {
        c = countStoneAtRow(col, _s[moveId]._row, row);
    }

    if (killId == -1) { // 走棋子
        if (c == 0) return true;
    } else { //吃棋子，跳过1个
        if (c == 1) return true;
    }
    return false;
}
bool MyWidget::canMoveBING(int moveId, int col, int row, int) {
    int dr = _s[moveId]._row - row;
    int dc = _s[moveId]._col - col;
    if (isBottomSide(moveId)) { //_s[moveId]._red
        if (dr < 0) return false;
        //没过河 不能拐弯
        if (abs(dc) > 0) {
            if (_s[moveId]._row >= 5) return false;
        }
    } else {
        //不能后退
        if (dr > 0) return false;
        //没过河 不能拐弯
        if (abs(dc) > 0) {
            if (_s[moveId]._row < 5) return false;
        }
    }

    int d = abs(dr) * 10 + abs(dc);
    //步长为1
    return d == 1 || d == 10;
}

//是否输了，bRed=红棋
bool MyWidget::isLost(bool bRed){
    if(isJIANGDead(bRed)){
        return true;
    }
    if(cannotMoveAnyStone(bRed)){
        return true;
    }
    return false;
}
//bRed=true:判断红棋，false：判断黑棋
bool MyWidget::cannotMoveAnyStone(bool bRed){
    //该红走的时候：红棋都不能走，红棋输
    //该黑走的时候：黑棋都不能走，黑棋输
    int min = 16, max = 32;
    if (bRed) {
        min = 0, max = 16;
    }

    for (int i = min; i < max; i++) {
        if (_s[i]._dead) continue;

        for (int row = 0; row <= 9; row++) {
            for (int col = 0; col <= 8; col++) {
                int killId = getStoneIdAt(col, row);
                //杀死自己的棋子
                if (killId != -1) {
                    if (_s[i]._red == _s[killId]._red)
                        continue;
                }

                if (canMove(i, col, row, killId)) {
                    return false;
                }
            }
        }
    }
    return true;

}

void MyWidget::iAmLost(bool bRed)
{
    m_winner=bRed?2:1;
}

bool MyWidget::isJIANGDead(bool bRed ){
//    int min = 16, max = 32;
//    if (bRed) {
//        min = 0, max = 16;
//    }
//    for (int i = min; i < max; i++) {
//        if (_s[i]._dead&&_s[i]._type==MyStone::JIANG)
//            return true;
//    }
//return false;

    if(bRed){
        if(redJIANGId<0) return false;
        return _s[redJIANGId]._dead;
    }
    else{
        if(blackJIANGId<0) return false;
        return _s[blackJIANGId]._dead;
    }
}

int MyWidget::judgeGameOver() {
    if (m_winner!=0)return m_winner;

    if (isLost(true)){
        return 2;
    }else if (isLost(false)){
         return 1;
    }

    return 0;
}
bool MyWidget::canMoveCHE(int moveId, int col, int row, int) {
    // 走直线，中间没有棋子
    int dr = _s[moveId]._row - row;
    int dc = _s[moveId]._col - col;
    if (abs(dr) == 0 && abs(dc) != 0) {
        int c = countStoneAtCol(row, _s[moveId]._col, col);
        if (c == 0) return true;
    } else if (abs(dr) != 0 && abs(dc) == 0) {
        int c = countStoneAtRow(col, _s[moveId]._row, row);
        if (c == 0) return true;
    }
    return false;
}
int MyWidget::countStoneAtCol(int row, int col1, int col2) {
    int c = 0;

    for (int i = 0; i < 32; i++) {
        if (_s[i]._row == row && !_s[i]._dead && _s[i]._col > qMin(col1, col2) && _s[i]._col < qMax(col1, col2)) {
            c++;
        }
    }
    return c;
}

int MyWidget::countStoneAtRow(int col, int row1, int row2) {
    int c = 0;

    for (int i = 0; i < 32; i++) {
        if (_s[i]._col == col && !_s[i]._dead && _s[i]._row > qMin(row1, row2) && _s[i]._row < qMax(row1, row2)) {
            c++;
        }
    }
    return c;
}

bool MyWidget::canSelect() { return false; }

void MyWidget::click(int id, int col, int row) {

    if (selectId == -1) {
        if (id != -1) {
            // if (canSelect()) {

            //没轮到红棋走，但点的是红棋，轮到红棋走，但点的不是红棋 --> 退出
            if ((bTranRed && _s[id]._red) || (!bTranRed && !_s[id]._red)) {
                selectId = id;
                update();
            }
        }
    } else {

        if (canMove(selectId, col, row, id)) {
            //走棋
//            logStep(selectId,id, col, row);
            //记录走棋
            saveStep(selectId, id,col, row, mPassSteps);
            //qDebug()<<"add step  "<<"moveId:"<<selectId<<"killId:"<<id<<"col:"<<col<<"row:"<<row;

            killStone(id);
            moveStone(selectId, col, row);
            if(isBottomSide(selectId)){
                mLastSelectIdRed=selectId;
            }else{
                mLastSelectIdBlack=selectId;
            }
            selectId = -1;

            mUseTime=0;
            update();
            m_winner=judgeGameOver();

            bells->play();
        }
    }
}

void MyWidget::mouseReleaseEvent(QMouseEvent *event) {
    QPoint pt = event->pos();

    if(mBackRect.contains(pt)){
        emit back_signal();
        return;
    }
    if(mRepentanceRect.contains(pt)){
        emit repentance_signal(1);
        return;
    }
    if(mSaveRect.contains(pt)){
        saveStone();
        return;
    }
    if(mLoadRect.contains(pt)){
        loadStone();
        return;
    }

    if (m_winner != 0) {
        QWidget::mouseReleaseEvent(event);
        return;
    }
    int row, col;
    bool bRet = getColRow(pt, col, row);
    if (!bRet) return;
    int clickId = -1;

    int idx = getStoneIdAt(col, row);
    if (idx >= 0) {
        clickId = idx;
    }

    click(clickId, col, row);
}

void MyWidget::killStone(int killId) {
    if (killId != -1) {
        _s[killId]._dead = true;
    }
}
void MyWidget::reliveStone(int killId) {
    if (killId != -1) {
        _s[killId]._dead = false;
    }
}

void MyWidget::moveStone(int moveId, int col, int row) {

    // 移动棋子
    _s[moveId]._row = row;
    _s[moveId]._col = col;
    bTranRed = !bTranRed;
}
void MyWidget::saveStep(int moveId, int killId, int col, int row, QVector<Step *> &steps) {
    // getColRow() ;
    int row1 = _s[moveId]._row;
    int col1 = _s[moveId]._col;
    Step *step = new Step;
    step->_colFrom = col1;
    step->_rowFrom = row1;
    step->_rowTo = row;
    step->_colTo = col;
    step->_killid = killId;
    step->_moveid = moveId;

    steps.append(step);
    //如果killid是将，，，、
    if(killId>-1&&_s[killId]._type==MyStone::JIANG){
//        QMediaPlayer * bells2 = new QMediaPlayer;

//        bells2->setMedia(QUrl(":/res/jiangjun.mp3"));
//        bells2->setVolume(100);
         bells2->play();
    }
}

//void MyWidget::logStep(int moveId, int killId, int col, int row)
//{
//}

void MyWidget::unfakeMove(Step *step) {
    reliveStone(step->_killid);
    moveStone(step->_moveid, step->_colFrom, step->_rowFrom);
}

void MyWidget::saveStone(){
    QString fn=QFileDialog::getSaveFileName(this,"保存残局",".","TEXT(*.txt)");
    if (fn.isEmpty()) return;

    QFile file(fn);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    QString s="";
    s+=QString::number(mLastSelectIdRed)+"\n";
    s+=QString::number( mLastSelectIdBlack)+"\n";
    s+= bTranRed?"1\n":"0\n" ;
    for (int i=0;i<32;i++) {
        //if (!_s[i]._dead){

        s+= QString::number( _s[i]._id)+","+QString::number( _s[i]._dead)+","
             +QString::number( _s[i]._col)+","+QString::number( _s[i]._row)+"\n";
        //}
    }

    file.write(s.toUtf8());
    file.close();
}
void MyWidget::loadStone(){

    QString fn=QFileDialog::getOpenFileName(this,"读取残局",".","TEXT(*.txt)");
    if (fn.isEmpty()) return;

    bool ok;
    QFile file(fn);
    ok=file.open(QIODevice::ReadOnly | QIODevice::Text);
    if(!ok){
        qDebug()<<"open file("<< fn << ") failed:"<<file.errorString();
        return;
    }
    int c=0;
    while(!file.atEnd()){

        QString  line=file.readLine();
        c++;
        if (c==1 ){
            mLastSelectIdRed=line.toInt(&ok);
            if(!ok)
                qDebug()<<"mLastSelectIdRed:failed";
            qDebug()<<"mLastSelectIdRed:"<<mLastSelectIdRed;
            continue;
        }
        if (c==2 ){
            mLastSelectIdBlack=line.toInt(&ok);
            if(!ok) qDebug()<<"mLastSelectIdBlack:failed";
            qDebug()<<"mLastSelectIdBlack:"<<mLastSelectIdBlack;
            continue;
        }
        if (c==3 ){
            bTranRed=line.trimmed()=="1" ;
            qDebug()<<"bTranRed:"<<bTranRed;
            continue;
        }

        if(line.isEmpty()) continue;
        QStringList list=line.split(",");
        if (list.isEmpty()) continue;
        int id=-1;
        if (list.count()>0){
            id = list.at(0).toInt(&ok);
            if(!ok) qDebug()<<"list.at(0):invalid number";
        }
        if(id<0)continue;

        if (list.count()>1){
            _s[id]._dead=list.at(1).toInt(&ok)!=0;
            if(!ok) qDebug()<<"list.at(1):invalid number";
        }
        if (list.count()>2){
            _s[id]._col=list.at(2).toInt(&ok);
            if(!ok) qDebug()<<"list.at(2):invalid number";
        }
        if (list.count()>3){
            _s[id]._row=list.at(3).toInt(&ok);
            if(!ok) qDebug()<<"list.at(3):invalid number";
        }
    }

    file.close();
}



