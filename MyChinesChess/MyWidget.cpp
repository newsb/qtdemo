#include "MyWidget.h"
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>
#include <QtMath>
/**todo :
 将军的时候，震动提示；
 * */
MyWidget::MyWidget(QWidget *parent)
    : QWidget(parent) {
    resize(600, 600);

    //    for (int i = 0; i < 32; ++i) {
    //        _s[i].init(i);
    //   }
    init(true);

#if 0
    for (int i = 0; i < 32; ++i) {
        if (i != 20 && i != 5) _s[i]._dead = true;
    }
#endif
}
void MyWidget::init(bool bRedSide) {
    for (int i = 0; i < 32; ++i) {
        _s[i].init(i);
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

MyWidget::~MyWidget() {}

void MyWidget::paintEvent(QPaintEvent *) {
    int colw = this->width() / (COL_COUNT + 2);
    int rowh = this->height() / (ROW_COUNT + 2);
    mColumnWidth = colw;
    mRowHeight = rowh;
    _r = colw < rowh ? colw / 2 : rowh / 2;

    QPainter p(this);

    drawBoard(p);

    //绘制棋子
    for (int i = 0; i < 32; ++i) {
        drawStone(p, i);
    }

    //绘制输赢结果。
    if (m_winner == 1 || m_winner == 2) {
        QRect rect(colw * 3, rowh * 5, colw * 4, rowh);
        p.setPen(Qt::red);
        p.drawText(rect, "GAME OVER", QTextOption(Qt::AlignCenter));
    }
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

    QPoint c = center(id);
    QRect rect = QRect(c.x() - _r, c.y() - _r, 2 * _r, 2 * _r);
    //    painter.setBrush(Qt::LinearGradientPattern);
    if (selectId == id) {
        painter.setBrush(QBrush(Qt::white));
        //        painter.setBrush(Qt::NoBrush);
    } else {
        painter.setBrush(QBrush(Qt::lightGray));
    }

    painter.setPen(Qt::darkYellow);
    painter.drawEllipse(c, _r + 5, _r + 5);

    painter.setPen(Qt::darkYellow);
    painter.drawEllipse(c, _r, _r);

    /* painter.setPen(Qt::green);
     painter.drawEllipse(c, _r - 5, _r - 5);
*/
 //todo :悔棋
    painter.setPen(Qt::black);
    if (_s[id]._red) {
        painter.setPen(Qt::red);
    }
    painter.setFont(QFont("微软雅黑", _r, 700));
    painter.drawText(rect, _s[id].getText(), QTextOption(Qt::AlignCenter));
}

void MyWidget::drawBoard(QPainter &p) {
    int colw = mColumnWidth;
    int rowh = mRowHeight;
    p.setRenderHint(QPainter::Antialiasing); //抗锯齿
    QPen pen = QPen(QColor(Qt::lightGray));
    pen.setWidth(3);
    p.setPen(pen);
    //竖线
    for (int i = 0; i <= COL_COUNT; i++) {
        if (i != COL_COUNT && i != 0) {
            p.drawLine(colw * (1 + i), rowh, colw * (1 + i), ((COL_COUNT / 2) + 1) * rowh);
            p.drawLine(colw * (1 + i), ((COL_COUNT / 2) + 2) * rowh, colw * (1 + i), height() - rowh);

        } else {
            p.drawLine(colw * (1 + i), rowh, colw * (1 + i), height() - rowh);
        }
    }
    //    pen.setColor(QColor(Qt::red));
    //    p.setPen(pen);
    //横线
    for (int i = 0; i <= ROW_COUNT; i++) {
        p.drawLine(colw, rowh * (1 + i), width() - colw, rowh * (1 + i));
    }
    //九宫格
    p.drawLine(colw * 4, rowh, 6 * colw, rowh * 3);
    p.drawLine(colw * 6, rowh, colw * 4, 3 * rowh);
    p.drawLine(colw * 4, rowh * 10, 6 * colw, rowh * 8);
    p.drawLine(colw * 6, rowh * 10, colw * 4, 8 * rowh);

    //炮 位置
    QPoint pt = QPoint(colw * 2, rowh * 3);
    QPainterPath path = this->getPaoBingPostionPath(pt);
    p.drawPath(path);

    pt.setX(colw * 8);
    path = this->getPaoBingPostionPath(pt);
    p.drawPath(path);

    pt.setY(rowh * 8);
    path = this->getPaoBingPostionPath(pt);
    p.drawPath(path);

    pt.setX(colw * 2);
    path = this->getPaoBingPostionPath(pt);
    p.drawPath(path);
    //上部 兵位置
    pt.setX(colw);
    pt.setY(rowh * 4);
    path = this->getPaoBingPostionPath(pt, 2);
    p.drawPath(path);
    pt.setX(colw * 3);
    path = this->getPaoBingPostionPath(pt);
    p.drawPath(path);
    pt.setX(colw * 5);
    path = this->getPaoBingPostionPath(pt);
    p.drawPath(path);
    pt.setX(colw * 7);
    path = this->getPaoBingPostionPath(pt);
    p.drawPath(path);
    pt.setX(colw * 9);
    path = this->getPaoBingPostionPath(pt, 1);
    p.drawPath(path);
    //下部 兵位置
    pt.setX(colw);
    pt.setY(rowh * 7);
    path = this->getPaoBingPostionPath(pt, 2);
    p.drawPath(path);
    pt.setX(colw * 3);
    path = this->getPaoBingPostionPath(pt);
    p.drawPath(path);
    pt.setX(colw * 5);
    path = this->getPaoBingPostionPath(pt);
    p.drawPath(path);
    pt.setX(colw * 7);
    path = this->getPaoBingPostionPath(pt);
    p.drawPath(path);
    pt.setX(colw * 9);
    path = this->getPaoBingPostionPath(pt, 1);
    p.drawPath(path);

    QRect rect = QRect(colw * 1, rowh * 5, colw * 3, rowh);
    p.setFont(QFont("华文隶书", 24));
    p.setPen(Qt::lightGray);
    p.drawText(rect, "楚河", QTextOption(Qt::AlignCenter));

    rect = QRect(colw * 6, rowh * 5, colw * 3, rowh);
    //    p.save();
    //    p.rotate(45);
    p.drawText(rect, "汉界", QTextOption(Qt::AlignCenter));
    //    p.restore();
}
QPoint MyWidget::center(int id) { return QPoint((_s[id]._col + 1) * mColumnWidth, (_s[id]._row + 1) * mRowHeight); }

bool MyWidget::getColRow(QPoint pt, int &col, int &row) {
    double d = 1.0 * pt.x() / mColumnWidth;
    col = qRound(d) - 1;
    d = 1.0 * pt.y() / mRowHeight;
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
    // yixia不用考虑目标位置是自己的棋子，这种情况已经过滤了
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

void MyWidget::judgeGameOver() {
    for (int i = 0; i < 32; i++) {
        if (_s[i]._type == MyStone::JIANG && _s[i]._dead) {
            if (_s[i]._red) {
                m_winner = 2;
            } else {
                m_winner = 1;
            }
            break;
        }
    }
    if (m_winner != 0) {
        qDebug() << "game over , m_winner:" << m_winner;
        return;
    }
    //该红走的时候：红棋都不能走，红棋输
    //该黑走的时候：黑棋都不能走，黑棋输
    int min = 16, max = 32;
    if (bTranRed) {
        min = 0, max = 16;
    }

    for (int i = min; i < max; i++) {
        if (_s[i]._dead) continue;

        for (int row = 0; row <= 9; row++) {
            for (int col = 0; col <= 8; col++) {
                int killId = getStoneIdAt(col, row);

                if (killId != -1) {
                    if (_s[i]._red == _s[killId]._red) continue;
                }

                if (canMove(i, col, row, killId)) {
                    return;
                }
            }
        }
    }
    if (bTranRed) { //红棋没有可走的了，黑旗赢
        m_winner = 2;
        qDebug() << "game over , m_winner:" << m_winner;
    } else {
        m_winner = 1;
        qDebug() << "game over , m_winner:" << m_winner;
    }
    return;
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
            killStone(id);
            moveStone(selectId, col, row);
            selectId = -1;
            update();
            judgeGameOver();
        }
    }
}
void MyWidget::mouseReleaseEvent(QMouseEvent *event) {
    if (m_winner != 0) {
        QWidget::mouseReleaseEvent(event);
        return;
    }
    QPoint pt = event->pos();
    int row, col;
    bool bRet = getColRow(pt, col, row);
    if (!bRet) return;
    int clickId = -1;

    int idx = getStoneIdAt(col, row);
    if (idx >= 0) {
        clickId = idx;
    }

    click(clickId, col, row);
    //    if (selectId == -1) {
    //        if (clickId != -1) {
    //            // if (canSelect()) {

    //            //没轮到红棋走，但点的是红棋，轮到红棋走，但点的不是红棋 --> 退出
    //            if ((bTranRed && _s[clickId]._red) || (!bTranRed && !_s[clickId]._red)) {
    //                selectId = clickId;
    //                update();
    //            }
    //        }
    //    } else {

    //        if (canMove(selectId, col, row, clickId)) {
    //            //走棋
    //            killStone(clickId);
    //            moveStone(selectId, col, row);
    //            selectId = -1;
    //            update();
    //            judgeGameOver();
    //        }
    //    }
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
