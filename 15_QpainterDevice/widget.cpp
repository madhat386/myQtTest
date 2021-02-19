#include "widget.h"
#include "ui_widget.h"
#include <QPainter>
#include <QPicture>

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);
    this->setFixedSize(600, 400);
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


    //QPicture绘图设备(不是用于画图，而是用于重现，记录绘图指令使用)
    QPicture pic;
    QPainter painter3;
    painter3.begin(&pic);

    pix.fill(Qt::white);
    painter3.setPen(QPen(Qt::cyan));
    painter3.drawEllipse(QPoint(150, 150), 100, 100);

    painter3.end();
    //保存
    pic.save("C:\\Users\\madha.KAERMORHEN\\Desktop\\picture.madhat");
}

void Widget::paintEvent(QPaintEvent*) {
    //加载图片
    QImage img;
    img.load(":/images/img.jpg");
    //Qimage可以修改像素
    for (int i = 0; i < 50; ++i) {
        for (int j = 0; j < 50; ++j) {
            QRgb color = qRgb(255, 0, 0);
            img.setPixel(i, j, color);
        }
    }

    QPainter painter(this);
    painter.drawImage(QPoint(0, 0), img);

    //利用QPicture重现绘图指令
    QPicture pic;
    pic.load("C:\\Users\\madha.KAERMORHEN\\Desktop\\picture.madhat");
    painter.drawPicture(0, 0, pic);


}

Widget::~Widget() {
    delete ui;
}
