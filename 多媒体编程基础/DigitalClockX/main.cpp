#include "DigitalClockX.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    DigitalClockX w;
    w.show();
    return a.exec();
}
