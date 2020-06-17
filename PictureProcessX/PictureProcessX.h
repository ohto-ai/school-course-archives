#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_PictureProcessX.h"

class PictureProcessX : public QMainWindow
{
    Q_OBJECT

public:
    PictureProcessX(QWidget *parent = Q_NULLPTR);

private:
    Ui::PictureProcessXClass ui;
};
