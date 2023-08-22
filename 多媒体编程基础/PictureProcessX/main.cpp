#include "PictureProcessX.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    PictureProcessX w;
    w.show();
    return a.exec();
}
