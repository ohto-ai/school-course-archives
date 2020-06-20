#pragma once

#include <QtWidgets/QMainWindow>
#include <QFileDialog>
#include "ImageWidget.h"
#include "ui_ImageViewerX.h"

class ImageViewerX : public QMainWindow
{
    Q_OBJECT

public:
    ImageViewerX(QWidget *parent = Q_NULLPTR);

private:
    friend class MultiMediaSystem;
    Ui::ImageViewerXClass ui;
    ImageWidget imageWidget;
};
