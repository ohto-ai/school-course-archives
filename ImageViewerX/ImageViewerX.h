#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ImageViewerX.h"

class ImageViewerX : public QMainWindow
{
    Q_OBJECT

public:
    ImageViewerX(QWidget *parent = Q_NULLPTR);

private:
    Ui::ImageViewerXClass ui;
};
