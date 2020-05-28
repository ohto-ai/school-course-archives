#include "ImageViewerX.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    ImageViewerX w;
    w.show();
    return a.exec();
}
