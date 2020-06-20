#include "MultiMediaSystem.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MultiMediaSystem w;
    w.show();
    return a.exec();
}
