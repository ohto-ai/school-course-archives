#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PageTest.h"
#include "ImageViewerX/ImageViewerX.h"
#include "VideoPlayerX/VideoPlayerX.h"
#include "PaintX/PaintX.h"
#include "NotepadX/NotepadXWindow.h"
#include "CameraX/CameraX.h"

class PageTest : public QMainWindow
{
    Q_OBJECT

public:
    PageTest(QWidget *parent = Q_NULLPTR);

private:
    Ui::PageTestClass ui;
    Ui::ImageViewerXClass uiImage;
    ImageWidget imageWidget;
};
