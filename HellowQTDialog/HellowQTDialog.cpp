#include "HellowQTDialog.h"

HellowQTDialog::HellowQTDialog(QWidget* parent)
    : QDialog(parent)
{
    resize(150, 150);//���öԻ����С
    label = new QLabel(this);
    //����������ʾ����
    label->setText("Hello Qt!");
    //���ñ�ǩλ�á���С
    label->setGeometry(0, 0, 100, 100);

}

HellowQTDialog::~HellowQTDialog()
{
}

