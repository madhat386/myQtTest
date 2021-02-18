#include "widget.h"
#include "ui_widget.h"
#include <QTimerEvent>
#include <QDebug>
#include <QTimer>

Widget::Widget(QWidget* parent) : QWidget(parent), ui(new Ui::Widget) {
    ui->setupUi(this);

    //启动定时器(1000毫秒间隔)
    timerId1 = startTimer(1000);
    timerId2 = startTimer(2000);

    //定时器的第二种方式
    QTimer* timer1 = new QTimer(this);
    //启动定时器,每隔0.5秒发送一个信号
    timer1->start(500);
    connect(timer1, &QTimer::timeout, [ = ]() {
        static int num = 0;
        ui->label_timer3->setText(QString::number(++num));
    });

}

Widget::~Widget() {
    delete ui;
}

void Widget::timerEvent(QTimerEvent* e) {
    static int num = 0;
    static int num2 = 0;
    if(e->timerId() == timerId1) {
        ui->label_timer->setText(QString::number(++num));
    } else if(e->timerId() == timerId2) {
        ui->label_timer2->setText(QString::number(++num2));
    }
}
