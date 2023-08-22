#include "CameraX.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    CameraX w;
    w.show();
    return a.exec();
}
