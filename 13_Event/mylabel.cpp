#include "mylabel.h"
#include <QDebug>
#include <QEvent>
#include <QMouseEvent>


MyLabel::MyLabel(QWidget* parent) : QLabel(parent) {



}

void MyLabel::enterEvent(QEvent* event) {
    qDebug() << "鼠标进入了";
}

void MyLabel::leaveEvent(QEvent* event) {
    qDebug() << "鼠标离开了";
}

void MyLabel::mouseMoveEvent(QMouseEvent* event) {
    //只让移动事件在左键按下的时候触发
    if(event->buttons() & Qt::LeftButton) {
        QString str = QString("鼠标移动了（按下左键）,x=%1,y=%2").arg(event->x()).arg(event->y());
        qDebug() << str;
    }
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
