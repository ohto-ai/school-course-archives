#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel> //���ͷ�ļ�

class HellowQTDialog : public QDialog
{
    Q_OBJECT
        QLabel* label; //��ӱ�ǩָ��
public:
    HellowQTDialog(QWidget* parent = nullptr);
    ~HellowQTDialog();
};
#endif // DIALOG_H
