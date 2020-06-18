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
    auto digitalClock = new DigitalClockX(ui.frameDigitalClock);

    ui.layoutImageViewer->addWidget(imageViewer);
    ui.layoutVideoPlayer->addWidget(videoPlayer);
    ui.layoutNotepad->addWidget(notepad);
    ui.layoutPaint->addWidget(paint);
    ui.layoutCamera->addWidget(camera);
    ui.layoutDigitalClock->addWidget(digitalClock);

    imageViewer->setWindowFlags(Qt::FramelessWindowHint);
    videoPlayer->setWindowFlags(Qt::FramelessWindowHint);
    notepad->setWindowFlags(Qt::FramelessWindowHint);
    paint->setWindowFlags(Qt::FramelessWindowHint);
    camera->setWindowFlags(Qt::FramelessWindowHint);
    digitalClock->setWindowFlags(Qt::FramelessWindowHint);
}
