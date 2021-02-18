#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>

class MyLabel : public QLabel {
    Q_OBJECT
public:
    explicit MyLabel(QWidget* parent = nullptr);

    //重写捕获事件方法
    void enterEvent(QEvent* event);
    void leaveEvent(QEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);

    //事件分发，Event事件
    bool event(QEvent* e);

signals:

public slots:
};

#endif // MYLABEL_H
