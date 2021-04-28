#include "gradientdemo.h"
#include <QPainter>
GradientDemo::GradientDemo(QWidget *parent) : QWidget(parent)
{

}


void GradientDemo::paintEvent(QPaintEvent *event)
{
#if 0
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing, true);
    QLinearGradient linearGradient(60, 50, 200, 200);
    linearGradient.setColorAt(0.2, Qt::white);
    linearGradient.setColorAt(0.6, Qt::green);
    linearGradient.setColorAt(1.0, Qt::black);
    p.setBrush(QBrush(linearGradient));
    p.drawEllipse(50, 50, 200, 150);

//    p.setBrush(Qt::NoBrush);
//    p.setPen(Qt::red);
//    p.drawRect(60, 50, 200, 200);
//    p.setPen(Qt::green);
//    p.drawRect(50, 50, 200, 150);

#endif

#if 0
    QPainter painter(this);
    const int r = 150;
    //创建一个角度渐变实例
    QConicalGradient conicalGradient(0, 0, 0);
    //0 度角设置为红色；
    conicalGradient.setColorAt(0.0, Qt::red);
    //将 60 度角设置为黄色
    conicalGradient.setColorAt(60.0/360.0, Qt::yellow);
    conicalGradient.setColorAt(120.0/360.0, Qt::green);
    conicalGradient.setColorAt(180.0/360.0, Qt::cyan);
    conicalGradient.setColorAt(240.0/360.0, Qt::blue);
    conicalGradient.setColorAt(300.0/360.0, Qt::magenta);
    //最后一句，我们将 1.0 处设置为红色，也就是重新回到起始处
    conicalGradient.setColorAt(1.0, Qt::red);
    //QPainter::translate(x, y)函数意思是，将坐标系的原点设置到 (x, y) 点。
    //原本坐标系原点位于左上角，我们使用translate(r, r)，将坐标原点设置为 (r, r)。这么一来，左上角的点的坐标就应该是 (-r, -r)。
    painter.translate(r, r);

    QBrush brush(conicalGradient);
    painter.setPen(Qt::NoPen);
    painter.setBrush(brush);
    //最后，我们使用drawEllipse()函数绘制圆盘。注意，由于我们已经把坐标原点设置为 (r, r)，因此，在绘制时，圆心应该是新的坐标 (0, 0)，而不是原来的 (r, r)。
    painter.drawEllipse(QPoint(0, 0), r, r);

#endif
#if 0
    QPainter painter(this);
    painter.fillRect(10, 10, 50, 100, Qt::red);
    painter.save();
    painter.translate(100, 0); // 向右平移 100px
    painter.fillRect(10, 10, 50, 100, Qt::yellow);
    painter.restore();
    painter.save();
    painter.translate(300, 0); // 向右平移 300px
    painter.rotate(30); // 顺时针旋转 30 度
    painter.fillRect(10, 10, 50, 100, Qt::green);
    painter.restore();
    painter.save();
    painter.translate(400, 0); // 向右平移 400px
    painter.scale(2, 3); // 横坐标单位放大 2 倍，纵坐标放大 3 倍
    painter.fillRect(10, 10, 50, 100, Qt::blue);
    painter.restore();
    painter.save();
    painter.translate(600, 0); // 向右平移 600px
    painter.shear(0, 1); // 横向不变，纵向扭曲 1 倍
    painter.fillRect(10, 10, 50, 100, Qt::cyan);
    painter.restore();
#endif

#if 1
    //将窗口矩形设置为左上角坐标为 (0, 0)，长和宽都是 200px。此时，坐标原点不变，还是左上角，但是，对于原来的 (400, 400) 点，
    //新的窗口坐标是 (200, 200)。我们可以理解成，逻辑坐标被“重新分配”。
    //这有点类似于translate()，但是，translate()函数只是简单地将坐标原点重新设置，
    //而setWindow()则是将整个坐标系进行了修改。这段代码的运行结果是将整个窗口进行了填充。
     QPainter painter(this);
     painter.setWindow(0, 0, 200, 200);
    painter.fillRect(0, 0, 200, 200, Qt::red);
    /**
    window 代表窗口坐标，viewport 代表物理坐标。
    也就是说，我们将物理坐标区域定义为左上角位于 (0, 0)，长高都是 200px 的矩形。然后还是绘制和上面一样的矩形。
    如果你认为运行结果是 1/4 窗口被填充，那就错了。实际是只有 1/16 的窗口被填充。
    这是由于，我们修改了物理坐标，但是没有修改相应的窗口坐标。
    默认的逻辑坐标范围是左上角坐标为 (0, 0)，长宽都是 400px 的矩形。
    当我们将物理坐标修改为左上角位于 (0, 0)，长高都是 200px 的矩形时，窗口坐标范围不变，
    也就是说，我们将物理宽 200px 映射成窗口宽 400px，物理高 200px 映射成窗口高 400px，所以，
    原始点 (200, 200) 的坐标变成了 ((0 + 200 * 200 / 400), (0 + 200 * 200 / 400)) = (100, 100)。
    */
//    painter.setViewport(0, 0, 200, 200);
//    painter.fillRect(0, 0, 200, 200, Qt::green);

//将坐标原点设置到 (200, 200) 处，横坐标范围是 [-200, 200]，纵坐标范围是 [-200, 200]
//    painter.translate(200, 200);

    /**
        坐标原点也是在窗口正中心，但是，我们将物理宽 400px 映射成窗口宽 320px，物理高 400px 映射成窗口高 640px，
        此时，横坐标范围是 [-160, 160]，纵坐标范围是 [-320, 320]。这种变换是简单的线性变换。
        假设原来有个点坐标是 (64， 60)，那么新的窗口坐标下对应的坐标应该是 ((-160 + 64 * 320 / 400), (-320 + 60 * 640 / 400)) = (-108.8, -224)。
    */
//    painter.setWindow(-160, -320, 320, 640);
#endif

}
