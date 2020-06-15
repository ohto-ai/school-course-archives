#include "PageTest.h"

PageTest::PageTest(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    auto view1 = new ImageViewerX(ui.tabImageViewer);
    auto view2 = new VideoPlayerX(ui.tabVideoPlayer);
    auto view3 = new NotepadXWindow(ui.tabNotepad);
	auto view4 = new PaintX(ui.tabPaint);
	auto view5 = new CameraX(ui.tabCamera);
}
