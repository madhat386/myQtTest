#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>

namespace Ui {
    class Widget;
}

class Widget : public QWidget {
    Q_OBJECT

public:
//    explicit Widget(QWidget* parent = nullptr);
    explicit Widget(QWidget* parent, QString name);
    ~Widget();
    QString name;

private:
    Ui::Widget* ui;
};

#endif // WIDGET_H
