#include "udp1.h"
#include "udp2.h"
#include <QApplication>

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);
    Udp1 u;
    u.show();
    Udp2 u2;
    u2.show();

    return a.exec();
}
