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
    //绘图事件
    void paintEvent(QPaintEvent*);
};

#endif // WIDGET_H
