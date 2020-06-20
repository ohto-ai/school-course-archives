#include "MultiMediaSystem.h"

MultiMediaSystem::MultiMediaSystem(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    setWindowIcon(QIcon(":/MultiMediaSystem/res/MultiMediaSystem.ico"));

    auto imageViewer = new ImageViewerX(ui.frameImageViewer);
    auto videoPlayer = new VideoPlayerX(ui.frameVideoPlayer);
    auto notepad = new NotepadXWindow(ui.frameNotepad);
    auto paint = new PaintX(ui.framePaint);
    auto camera = new CameraX(ui.frameCamera);
    auto digitalClock = new DigitalClockX(ui.frameDigitalClock);
    auto pictureProcess = new PictureProcessX(ui.framePictureProcess);

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

    imageViewer->setWindowFlags(Qt::FramelessWindowHint);
    videoPlayer->setWindowFlags(Qt::FramelessWindowHint);
    notepad->setWindowFlags(Qt::FramelessWindowHint);
    paint->setWindowFlags(Qt::FramelessWindowHint);
    camera->setWindowFlags(Qt::FramelessWindowHint);
    digitalClock->setWindowFlags(Qt::FramelessWindowHint);
    pictureProcess->setWindowFlags(Qt::FramelessWindowHint);

    connect(ui.tabWidget, &QTabWidget::currentChanged, [=](int index)
        {
            ui.tabWidget->currentWidget() == ui.tabCamera ? camera->start(): camera->stop();
            ui.tabWidget->currentWidget() == ui.tabVideoPlayer ? videoPlayer->turnForeground() : videoPlayer->turnBackground();
        });
}
