#include "HellowQTDialog.h"

HellowQTDialog::HellowQTDialog(QWidget* parent)
    : QDialog(parent)
{
    resize(150, 150);//设置对话框大小
    label = new QLabel(this);
    //设置文字显示内容
    label->setText("Hello Qt!");
    //设置标签位置、大小
    label->setGeometry(0, 0, 100, 100);

}

HellowQTDialog::~HellowQTDialog()
{
}

