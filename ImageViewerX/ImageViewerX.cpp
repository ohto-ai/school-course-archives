#include "ImageViewerX.h"

ImageViewerX::ImageViewerX(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setCentralWidget(&imageWidget);

    connect(ui.actionOpen, &QAction::triggered, &imageWidget, &ImageWidget::loadDialog);
}
