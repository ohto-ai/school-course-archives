#include "MultiMidiaSystem.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MultiMidiaSystem w;
    w.show();
    return a.exec();
}
