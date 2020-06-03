#pragma once

#include <QtWidgets/QMainWindow>
#include <QColorDialog>
#include <QFileDialog>
#include "PaintWidget.h"
#include "ui_PaintX.h"

class PaintX : public QMainWindow
{
    Q_OBJECT
public:
    PaintX(QWidget *parent = Q_NULLPTR);

private:
    Ui::PaintXClass ui;
    QPoint mouseCoord;
};
