#include "PaintX.h"

PaintX::PaintX(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    new PaintWidget(ui.sketchpad);    
}
