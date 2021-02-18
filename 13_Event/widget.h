#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
    class Widget;
}

class Widget : public QWidget {
    Q_OBJECT

public:
    explicit Widget(QWidget* parent = nullptr);
    ~Widget();

private:
    Ui::Widget* ui;

    //定时器时间
    void timerEvent(QTimerEvent* e);
    //定时器的id
    int timerId1;
    int timerId2;
};

#endif // WIDGET_H
