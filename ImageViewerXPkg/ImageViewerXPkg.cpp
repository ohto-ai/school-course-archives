#include "ImageViewerXPkg.h"
#include "../ImageViewerX/ImageViewerX.h"
#include "../NotepadX/NotepadXWindow.h"
#include <QtWidgets/QApplication>

ImageViewerXPkg::ImageViewerXPkg()
{
}

void ImageViewerXPkg::runImageViewX()
{
    int argc = 1;
    char* argv[] = {
        "ImageViewXPkg.dll"
    };
    QApplication a(argc, argv);
    ImageViewerX w;
    w.show();
    a.exec();
}

void ImageViewerXPkg::runNotepadX()
{
    int argc = 1;
    char* argv[] = {
        "ImageViewXPkg.dll"
    };
    QApplication a(argc, argv);
    NotepadXWindow mainWindow;

    mainWindow.show();
    a.exec();
}
