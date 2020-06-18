#include "AnalogClock.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    AnalogClock w;
    w.show();
    return a.exec();
}
