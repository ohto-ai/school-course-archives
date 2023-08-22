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
    /// ����ʱ��
    /// </summary>
    /// <param name="painter">����</param>
    /// <param name="h">ʱ</param>
    /// <param name="m">��</param>
    /// <param name="s">��</param>
    void paintClock(QPainter& painter);

    friend class MultiMediaSystem;

    Ui::DigitalClockXClass ui;
    QImage digitalImages[11];
    QImage background;
    int digitalWidth = 30;
    int digitalHeight = 30;
    int freshTimer = 0;
};
