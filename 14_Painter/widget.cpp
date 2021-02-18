#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPen>

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);



}

Widget::~Widget() {
    delete ui;
}

//实现绘图事件(自动调用)
void Widget::paintEvent(QPaintEvent*) {
    //创建画家
    QPainter painter(this);//this代表绘图设备（一张纸）
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

}
