#ifndef UDP1_H
#define UDP1_H

#include <QWidget>
//引入QUdp的头文件前需要在pro文件中添加模块network
#include <QUdpSocket>

namespace Ui {
    class Udp1;
}

class Udp1 : public QWidget {
    Q_OBJECT

public:
    explicit Udp1(QWidget* parent = nullptr);
    ~Udp1();
    //套接字
    QUdpSocket* udp;

private:
    Ui::Udp1* ui;
};

#endif // UDP1_H
