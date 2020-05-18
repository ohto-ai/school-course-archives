# pragma execu
#include <QApplication>
#include "Dialog.h"


int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	Dialog dlg;

	dlg.show();
	return a.exec();
}