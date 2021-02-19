#include "widget.h"
#include "ui_widget.h"
#include <QPainter>

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    //QPixmap 做绘图设备（对不同平台显示做了优化）
    QPixmap pix(300, 300);
    QPainter painter(&pix);
    //设置默认填充色
    pix.fill(Qt::white);
    painter.setPen(QPen(Qt::green));
    painter.drawEllipse(QPoint(150, 150), 100, 100);

    //保存到硬盘上
    pix.save("C:\\Users\\madha.KAERMORHEN\\Desktop\\yuan.png");

    //QImage做绘图设备(对像素级访问做了优化)
    QImage img(300, 300, QImage::Format_RGB32);
    img.fill(Qt::yellow);
    QPainter painter2(&img);
    painter2.setPen(QPen(Qt::red));
    painter2.drawRect(100, 100, 100, 100);
    img.save("C:\\Users\\madha.KAERMORHEN\\Desktop\\fang.png");



}

Widget::~Widget() {
    delete ui;
}
