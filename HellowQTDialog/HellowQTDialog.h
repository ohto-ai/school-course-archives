#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include <QLabel> //添加头文件

class HellowQTDialog : public QDialog
{
    Q_OBJECT
        QLabel* label; //添加标签指针
public:
    HellowQTDialog(QWidget* parent = nullptr);
    ~HellowQTDialog();
};
#endif // DIALOG_H
