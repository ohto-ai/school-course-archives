#include "MediaPlayerXPre.h"
#include <QtWidgets/QApplication>
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    if (!config::loadConfig() || config::GlobalConfig.empty())
        config::resetConfig();

    MediaPlayerXPre w;
    w.show();
    return a.exec();
}
