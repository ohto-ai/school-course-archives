#include <QApplication>
#include "NotepadXWindow.h"


int main(int argc, char* argv[])
{
	QApplication a(argc, argv);
	NotepadXWindow mainWindow;

	mainWindow.show();
	return a.exec();
}