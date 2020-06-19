#pragma once

#include <QtWidgets/QMainWindow>
#include "../ImageViewerX/ImageViewerX.h"
#include "../VideoPlayerX/VideoPlayerX.h"
#include "../PaintX/PaintX.h"
#include "../NotepadX/NotepadXWindow.h"
#include "../CameraX/CameraX.h"
#include "../DigitalClockX/DigitalClockX.h"
#include "../PictureProcessX/PictureProcessX.h"
#include "../AuthorInformation/AuthorInformation.h"
#include "ui_MultiMidiaSystem.h"

class MultiMidiaSystem : public QMainWindow
{
    Q_OBJECT

public:
    MultiMidiaSystem(QWidget *parent = Q_NULLPTR);

private:
    Ui::MultiMidiaSystemClass ui;
    AuthorInformation about{ this };
};
