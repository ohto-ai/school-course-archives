#include "HellowQTUI.h"
#include <QApplication>

int main(int argc, char* argv[])
{
    QApplication a(argc, argv);
    HellowQTUI w;
    w.show();
    return a.exec();
}
