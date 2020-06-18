#pragma once

#include <QtWidgets/QMainWindow>
#include <QTime>
#include <QPainter>
#include <QTimerEvent>
#include "ui_AnalogClock.h"

class AnalogClock : public QMainWindow
{
    Q_OBJECT

public:
    AnalogClock(QWidget *parent = Q_NULLPTR);
    virtual void paintEvent(QPaintEvent*);
    virtual void timerEvent(QTimerEvent*);

private:
    int m_timerId;
    Ui::AnalogClockClass ui;
};
