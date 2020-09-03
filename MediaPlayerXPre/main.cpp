#include "MediaPlayerXPre.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MediaPlayerXPre w;
    w.show();
    return a.exec();
}
