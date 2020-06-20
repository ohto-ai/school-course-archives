#pragma once

#include <QtWidgets/QMainWindow>
#include <QPainter>
#include <QTime>
#include "ui_DigitalClockX.h"

class DigitalClockX : public QMainWindow
{
    Q_OBJECT

public:
    DigitalClockX(QWidget *parent = Q_NULLPTR);
    virtual void paintEvent(QPaintEvent*);
    virtual void timerEvent(QTimerEvent*);
private:
    /// <summary>
    /// 绘制时钟
    /// </summary>
    /// <param name="painter">画家</param>
    /// <param name="h">时</param>
    /// <param name="m">分</param>
    /// <param name="s">秒</param>
    void paintClock(QPainter& painter);

    friend class MultiMediaSystem;

    Ui::DigitalClockXClass ui;
    QImage digitalImages[11];
    QImage background;
    int digitalWidth = 30;
    int digitalHeight = 30;
    int freshTimer = 0;
};
