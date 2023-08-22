#include "PaintX.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PaintX w;
    w.show();
    return a.exec();
}
