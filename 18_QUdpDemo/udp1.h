#ifndef UDP1_H
#define UDP1_H

#include <QWidget>

namespace Ui {
class Udp1;
}

class Udp1 : public QWidget
{
    Q_OBJECT

public:
    explicit Udp1(QWidget *parent = nullptr);
    ~Udp1();

private:
    Ui::Udp1 *ui;
};

#endif // UDP1_H
