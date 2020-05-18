#include "HellowQTUI.h"
#include "ui_dialog.h"

HellowQTUI::HellowQTUI(QWidget* parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
}

HellowQTUI::~HellowQTUI()
{
    delete ui;
}

