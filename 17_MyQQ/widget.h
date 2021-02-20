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

signals:
//关闭窗口发送信号
    void closeWidget();

private:
    Ui::Widget* ui;
    //重写关闭事件
    void closeEvent(QCloseEvent*);
};


#endif // WIDGET_H
