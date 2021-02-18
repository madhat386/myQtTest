#include "mylabel.h"
#include <QDebug>
#include <QEvent>

MyLabel::MyLabel(QWidget* parent) : QLabel(parent) {



}

void MyLabel::enterEvent(QEvent* event) {
    qDebug() << "鼠标进入了";
}

void MyLabel::leaveEvent(QEvent* event) {
    qDebug() << "鼠标离开了";
}

void MyLabel::mouseMoveEvent(QMouseEvent* event) {
    qDebug() << "鼠标移动了（按下状态）";
}

void MyLabel::mousePressEvent(QMouseEvent* event) {
    qDebug() << "鼠标按下了";
}

void MyLabel::mouseReleaseEvent(QMouseEvent* event) {
    qDebug() << "鼠标释放了";
}
