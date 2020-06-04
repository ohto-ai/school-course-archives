#include "ImageViewerX.h"

ImageViewerX::ImageViewerX(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    setCentralWidget(&imageWidget);

    connect(ui.actionOpen, &QAction::triggered, [=]
        {
            imageWidget.load(QFileDialog::getOpenFileName(this, "Open", "/", "Image file(*.bmp;*.png;*.jpg;*.jpeg;)"));
        });
}
