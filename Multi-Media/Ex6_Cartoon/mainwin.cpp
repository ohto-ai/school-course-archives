#include "mainwin.h"
#include "ui_mainwin.h"
#include <QPainter>
#include <QString>

MainWin::MainWin(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWin)
{
    ui->setupUi(this);
    setWindowTitle("卡通效果");
    resize(640,480);
    id1=startTimer(20);
    num=0;
 }

MainWin::~MainWin()
{
    delete ui;
}

void MainWin::timerEvent(QTimerEvent *)
{
    if (num == 6)
            num = 0;
     else   num++;
    update();
}

void MainWin::paintEvent(QPaintEvent *)
{

    QPixmap *pix=new QPixmap(size().width(),size().height());;
    pix->load("img/girl"+QString::number(num)+".bmp");
    QPainter pt(this);
    pt.drawPixmap(0,0,*pix);

}

