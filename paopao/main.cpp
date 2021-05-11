#include "widget.h"
#include "gameview.h"

#include <QApplication>

#include <QtWidgets>
#include "items.h"


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
#if 0
    QGraphicsScene scene(0, 0, 800, 800);
        QGraphicsView view(&scene);
        view.setFixedSize(1000, 1000);
        view.setMaximumSize(1000, 1000);
        view.setMinimumSize(1000, 1000);

//        QFont font = a.font();
//        font.setPointSize(20);
//        auto text = new QGraphicsTextItem("Hello");
//        text->setFont(font);
//        text->setPos(100, 100);
//        text->setZValue(1);
//        scene.addItem(text);

//        QPropertyAnimation anim(text, "pos");
//        anim.setDuration(5000);//设置动画周期
//        anim.setStartValue(QPointF(0, 0));
//        anim.setEndValue(QPointF(500, 500));
//        anim.setEasingCurve(QEasingCurve(QEasingCurve::OutCubic));//设置变换曲线
//        anim.setLoopCount(4);
//        anim.start();

//        QPropertyAnimation animRotate(text, "rotation");
//        animRotate.setDuration(5000);
//        animRotate.setStartValue(0);
//        animRotate.setEndValue(360);
//        animRotate.setLoopCount(4);
//        anim.setEasingCurve(QEasingCurve(QEasingCurve::InCurve));
//        animRotate.start();

        //自定义Item
        auto cc = new ColorFulCircle(100, 100, Qt::red);
        cc->setPos(500, 500);
        scene.addItem(cc);

        QPropertyAnimation ccAnim(cc, "pos");
        ccAnim.setDuration(5000);
        ccAnim.setStartValue(QPointF(500, 500));
        ccAnim.setEndValue(QPointF(0, 0));
        ccAnim.setLoopCount(4);
        ccAnim.start();

        QPropertyAnimation ccAnimColor(cc, "color");
        ccAnimColor.setDuration(5000);
        ccAnimColor.setStartValue(QColor(Qt::red));
        ccAnimColor.setEndValue(QColor(Qt::yellow));
        ccAnimColor.setLoopCount(4);
        ccAnimColor.start();

        view.show();
#endif
            GameView w;
            w.show();

//    ————————————————
//    版权声明：本文为CSDN博主「hao_zong_yin」的原创文章，遵循CC 4.0 BY-SA版权协议，转载请附上原文出处链接及本声明。
//    原文链接：https://blog.csdn.net/hao_zong_yin/article/details/73826257
#if 0

            QGraphicsItem *ball = new QGraphicsEllipseItem(0, 0, 20, 20);
            ball->setTransformOriginPoint(ball->boundingRect().center());
            QTimeLine *timer = new QTimeLine(5000);
            timer->setLoopCount(0);        //无限循环
            timer->setFrameRange(0, 100);//frameChanged()发出的值在0-100之间
            timer->setCurveShape(QTimeLine::SineCurve);    //frameChanged()发出的值像sin曲线一样，1,2,...,99,100,99,...,2,1
            timer->setUpdateInterval(25);    //更新频率（也就是frameChanged(int)的执行速度），每25ms更新一次，相当于每秒40帧，
            QObject::connect(timer, &QTimeLine::frameChanged, [=](int frame){
                    //_st是一个QGraphicsItem
                    QRectF rect = ball->boundingRect();
                    QPointF pt = ball->boundingRect().center();
                    qreal scaleX_Y = (frame+50) / 100.0;
                    QTransform tran;
                    tran.translate(pt.x(), pt.y());
                    tran.scale(scaleX_Y, scaleX_Y);
                    ball->setTransform(tran);
                    QTransform t;
                    t.translate(-pt.x(), -pt.y());
                    ball->setTransform(t, true);
             });

             QGraphicsItemAnimation *animation = new QGraphicsItemAnimation;
             animation->setItem(ball);
             animation->setTimeLine(timer);

                 for (int i = 0; i < 200; ++i){
                    // animation->setPosAt(i / 200.0, QPointF(i, i));
                     qreal xx=1.0*i/100;
                     qreal yy=1.0*i/100;
                     animation->setScaleAt(i / 200.0,xx,yy);
                 }

                 QGraphicsScene *scene2 = new QGraphicsScene;
                 scene2->setSceneRect(0, 0, 250, 250);
                 scene2->addItem(ball);

                 QGraphicsView *view2 = new QGraphicsView(scene2);
                 view2->show();
                 timer->start();

 #endif


    return a.exec();
}
