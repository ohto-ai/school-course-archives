#include "OptionDialog.h"

OptionDialog::OptionDialog(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

OptionDialog::~OptionDialog()
{
}

void OptionDialog::moveEvent(QMoveEvent* e)
{
    auto& configOptionDialog = config::GlobalConfig["OptionDialog"];
    configOptionDialog["x"] = x();
    configOptionDialog["y"] = y();
}

void OptionDialog::resizeEvent(QResizeEvent* e)
{
    auto& configOptionDialog = config::GlobalConfig["OptionDialog"];
    configOptionDialog["width"] = width();
    configOptionDialog["height"] = height();
}