#ifndef MAINWIN_H
#define MAINWIN_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWin; }
QT_END_NAMESPACE

class MainWin : public QMainWindow
{
    Q_OBJECT

public:
    MainWin(QWidget *parent = nullptr);
    ~MainWin();

private:
    Ui::MainWin *ui;
    int id1;
    int num;//图号

protected:
    void timerEvent(QTimerEvent *);
    void paintEvent(QPaintEvent *);
};
#endif // MAINWIN_H
