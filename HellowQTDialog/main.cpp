#include "HellowQTDialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	HellowQTDialog w;
	w.show();
	return a.exec();
}
