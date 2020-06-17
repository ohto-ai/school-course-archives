#include "PageTest.h"

PageTest::PageTest(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    auto imageViewer = new ImageViewerX(ui.frameImageViewer);
    auto videoPlayer = new VideoPlayerX(ui.frameVideoPlayer);
    auto notepad = new NotepadXWindow(ui.frameNotepad);
	auto paint = new PaintX(ui.framePaint);
	auto camera = new CameraX(ui.frameCamera);

    ui.layoutImageViewer->addWidget(imageViewer);
    ui.layoutVideoPlayer->addWidget(videoPlayer);
    ui.layoutNotepad->addWidget(notepad);
    ui.layoutPaint->addWidget(paint);
    ui.layoutCamera->addWidget(camera);

    imageViewer->setWindowFlags(Qt::FramelessWindowHint);
    videoPlayer->setWindowFlags(Qt::FramelessWindowHint);
    notepad->setWindowFlags(Qt::FramelessWindowHint);
    paint->setWindowFlags(Qt::FramelessWindowHint);
    camera->setWindowFlags(Qt::FramelessWindowHint);
}
