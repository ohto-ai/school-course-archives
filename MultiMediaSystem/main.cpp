#include "MultiMediaSystem.h"
#include <QtWidgets/QApplication>
#include <QSplashScreen>

int main(int argc, char *argv[])
{
    using namespace std::chrono;
    QApplication a(argc, argv);
    QSplashScreen splashScreen(QPixmap(":/MultiMediaSystem/res/splash.png"));
    splashScreen.show();
    std::this_thread::sleep_for(1s);
    MultiMediaSystem w;
    splashScreen.close();
    w.show();
    return a.exec();
}
