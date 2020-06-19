#include "MultiMidiaSystem.h"

MultiMidiaSystem::MultiMidiaSystem(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    setWindowIcon(QIcon(":/MultiMidiaSystem/res/MultiMidiaSystem.ico"));

    auto imageViewer = new ImageViewerX(ui.frameImageViewer);
    auto videoPlayer = new VideoPlayerX(ui.frameVideoPlayer);
    auto notepad = new NotepadXWindow(ui.frameNotepad);
    auto paint = new PaintX(ui.framePaint);
    auto camera = new CameraX(ui.frameCamera);
    auto digitalClock = new DigitalClockX(ui.frameDigitalClock);
    auto pictureProcess = new PictureProcessX(ui.framePictureProcess);
    //auto authorInformation = new AuthorInformation(ui.frameAuthorInformation);

    connect(imageViewer->ui.actionAbout, &QAction::triggered, &about, &AuthorInformation::show);
    connect(videoPlayer->ui.actionAbout, &QAction::triggered, &about, &AuthorInformation::show);
    connect(notepad->ui.actionAbout, &QAction::triggered, &about, &AuthorInformation::show);
    connect(paint->ui.actionAbout, &QAction::triggered, &about, &AuthorInformation::show);
    connect(camera->ui.actionAbout, &QAction::triggered, &about, &AuthorInformation::show);
    connect(digitalClock->ui.actionAbout, &QAction::triggered, &about, &AuthorInformation::show);
    connect(pictureProcess->ui.actionAbout, &QAction::triggered, &about, &AuthorInformation::show);

    ui.layoutImageViewer->addWidget(imageViewer);
    ui.layoutVideoPlayer->addWidget(videoPlayer);
    ui.layoutNotepad->addWidget(notepad);
    ui.layoutPaint->addWidget(paint);
    ui.layoutCamera->addWidget(camera);
    ui.layoutDigitalClock->addWidget(digitalClock);
    ui.layoutPictureProcess->addWidget(pictureProcess);
    //ui.layoutAuthorInformation->addWidget(authorInformation);

    imageViewer->setWindowFlags(Qt::FramelessWindowHint);
    videoPlayer->setWindowFlags(Qt::FramelessWindowHint);
    notepad->setWindowFlags(Qt::FramelessWindowHint);
    paint->setWindowFlags(Qt::FramelessWindowHint);
    camera->setWindowFlags(Qt::FramelessWindowHint);
    digitalClock->setWindowFlags(Qt::FramelessWindowHint);
    pictureProcess->setWindowFlags(Qt::FramelessWindowHint);
   // authorInformation->setWindowFlags(Qt::FramelessWindowHint);
}
