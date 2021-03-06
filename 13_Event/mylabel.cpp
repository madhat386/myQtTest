#include "mylabel.h"
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>


MyLabel::MyLabel(QWidget* parent) : QLabel(parent) {
    //开启鼠标移入自动触发move事件，而无需主动按下任何键
    this->setMouseTracking(true);
}

void MyLabel::enterEvent(QEvent* event) {
    qDebug() << "鼠标进入了";
}

void MyLabel::leaveEvent(QEvent* event) {
    qDebug() << "鼠标离开了";
}

void MyLabel::mouseMoveEvent(QMouseEvent* event) {
    //只让移动事件在左键按下的时候触发
//    if(event->buttons() & Qt::LeftButton) {
//        QString str = QString("鼠标移动了（按下左键）,x=%1,y=%2").arg(event->x()).arg(event->y());
//        qDebug() << str;
//    }

    qDebug() << "鼠标移动了";
}

void MyLabel::mousePressEvent(QMouseEvent* event) {
    if(event->button() == Qt::LeftButton) {
        qDebug() << "鼠标按下了左键";
    } else if(event->button() == Qt::RightButton) {
        qDebug() << "鼠标按下了右键";
    }
}

void MyLabel::mouseReleaseEvent(QMouseEvent* event) {
    qDebug() << "鼠标释放了";
}

bool MyLabel::event(QEvent* e) {
    if(e->type() == QEvent::MouseButtonPress) {
        qDebug() << "Event:鼠标按下了";
        return true;//当return true的时候这个事件就不会再分发下去了
    }

    //其他事件returnfalse,交给后续事件(父类方法)继续处理
    QMouseEvent* ev = static_cast<QMouseEvent*>(e);
    return QLabel::event(ev);
}
