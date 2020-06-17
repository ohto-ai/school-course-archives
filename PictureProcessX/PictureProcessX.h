#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PictureProcessX.h"

class PictureProcessX : public QMainWindow
{
    Q_OBJECT

public:
    PictureProcessX(QWidget *parent = Q_NULLPTR);

private:
    void updateImageView();

    Ui::PictureProcessXClass ui;
    QImage oriImage;
};
