#pragma once

#include <QtWidgets/QMainWindow>
#include "../VideoPlayerX/VideoPlayerX.h"
#include "../PaintX/PaintX.h"
#include "../NotepadX/NotepadXWindow.h"
#include "../CameraX/CameraX.h"
#include "../DigitalClockX/DigitalClockX.h"
#include "../PictureProcessX/PictureProcessX.h"
#include "../AuthorInformation/AuthorInformation.h"
#include "ui_MultiMediaSystem.h"

class MultiMediaSystem : public QMainWindow
{
    Q_OBJECT

public:
    MultiMediaSystem(QWidget *parent = Q_NULLPTR);

private:
    enum: int {
        MEDIA_DIGITALCLOCK
        , MEDIA_IMAGEVIEWER
        , MEDIA_PICTUREPROCESS
        , MEDIA_VIDEOPLAYER
        , MEDIA_NOTEPAD
        , MEDIA_PAINT
        , Media_CAMERA
    };

    Ui::MultiMediaSystemClass ui;
    AuthorInformation about{ this };
};
