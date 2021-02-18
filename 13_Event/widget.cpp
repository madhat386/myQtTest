#include "widget.h"
#include "ui_widget.h"
#include <QTimerEvent>
#include <QDebug>
#include <QTimer>
#include <QMouseEvent>

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

    //点击按钮暂停定时器
    connect(ui-> pushButton, &QPushButton::clicked, [ = ]() {
        timer1->stop();
    });
    connect(ui-> pushButton_2, &QPushButton::clicked, [ = ]() {
        timer1->start();
    });


    //给mylabel做事件的过滤器拦截(参数this的意义通过父窗口给label安装过滤器)
    ui->label->installEventFilter(this);
    //重写自己（窗口）的eventFilter事件




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

//重写自己（窗口）的eventFilter事件
bool Widget::eventFilter(QObject* obj, QEvent* e) {
    if(obj == ui->label) {
        if(e->type() == QEvent::MouseButtonPress) {
            //转换事件类型
            QMouseEvent* ev = static_cast<QMouseEvent*>(e);
            QString str = QString("事件过滤器，鼠标按下了，x=%1,y=%2").arg(ev->x()).arg(ev->y());
            qDebug() << str;
            return true;
        }
    }

    //其他让默认父类方法处理
    return QWidget::eventFilter(obj, e);
}
