#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class HellowQTUI : public QDialog
{
    Q_OBJECT

public:
    HellowQTUI(QWidget* parent = nullptr);
    ~HellowQTUI();

private:
    Ui::Dialog* ui;
};
#endif // DIALOG_H
