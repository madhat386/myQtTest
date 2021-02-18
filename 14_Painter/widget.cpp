#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPen>

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    this->posX = 10;

    connect(ui->pushButton, &QPushButton::clicked, [ = ]() {
        //让成员属性posX的值增加，以便手动触发绘图事件的时候可以改变绘制图片的位置
        posX += 10;
        //手动调用从新绘图的事件
        this->update();
    });


}

Widget::~Widget() {
    delete ui;
}

//实现绘图事件(自动调用)
void Widget::paintEvent(QPaintEvent*) {
    //创建画家
    QPainter painter(this);//this代表绘图设备（一张纸）

    //高级设置
    painter.drawEllipse(QPoint(100, 100), 50, 50);
    //设置抗锯齿能力(影响性能)
    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawEllipse(QPoint(200, 100), 50, 50);

    painter.drawRect(QRect(20, 20, 50, 50));
    //移动画家
    painter.translate(QPoint(100, 0));
    //保存画家状态
    painter.save();
    painter.translate(QPoint(200, 200));
    //还原画家状态(还原到之前保存的状态)
    painter.restore();
    painter.drawRect(QRect(100, 20, 50, 50));

    //画一个图片
    //如果出屏幕，强制变回10
    if(posX > this->width()) {
        posX = 10;
    }
    //先往回移动一点距离调整下初始位置
    painter.translate(QPoint(-100, 0));
    painter.drawPixmap(posX, 10, 200, 200, QPixmap(":images/img.jpg"));



    /*

    //设置画笔颜色
    QPen pen(QColor(255, 0, 0));
    //设置笔宽
    pen.setWidth(3);
    //设置笔的风格(比如虚线)
    pen.setStyle(Qt::DashLine);
    //画家拿起画笔
    painter.setPen(pen);
    //创建画刷，用来填充封闭区域的颜色
    QBrush brush(Qt::cyan);
    //设置画刷的风格
    brush.setStyle(Qt::Dense4Pattern);
    //让画家使用画刷
    painter.setBrush(brush);
    //开始绘画
    painter.drawLine(QPoint(0, 0), QPoint(100, 100));
    //画( 椭)圆
    painter.drawEllipse(QPoint(100, 100), 50, 50);
    //画矩形
    painter.drawRect(QRect(QPoint(100, 100), QPoint(200, 200)));
    //画字体
    painter.drawText(QRect(10, 250, 200, 50), "万事皆虚，一切皆允");

    */


}
