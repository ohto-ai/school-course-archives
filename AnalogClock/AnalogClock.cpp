#include "AnalogClock.h"

AnalogClock::AnalogClock(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    m_timerId = startTimer(10);
}

void AnalogClock::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    static const QPoint hourHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -40)
    };
    static const QPoint minuteHand[3] = {
        QPoint(7, 8),
        QPoint(-7, 8),
        QPoint(0, -70)
    };
    static const QPoint secondHand[3] = {
        QPoint(5, 8),
        QPoint(-5, 8),
        QPoint(0, -90)
    };


    QColor hourColor(127, 0, 127);
    QColor minuteColor(0, 127, 127, 191);
    QColor secondColor(240, 40, 40, 240);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.translate(width() / 2, height() / 2);

    int side = qMin(width(), height());
    painter.scale(side / 200.0, side / 200.0);

    QTime time = QTime::currentTime();


    painter.save(); // ³õÊ¼×´Ì¬
    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawConvexPolygon(hourHand, 3);
    painter.restore();// »Ö¸´³õÊ¼×´Ì¬

    painter.save(); // ³õÊ¼×´Ì¬
    painter.setPen(hourColor);
    for (int i = 0; i < 12; ++i) {
        painter.drawLine(88, 0, 96, 0);
        painter.rotate(30.0);
    }
    painter.restore();// »Ö¸´³õÊ¼×´Ì¬


    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(minuteColor);
    painter.rotate(6.0 * (time.minute() + time.second() / 60.0));
    painter.drawConvexPolygon(minuteHand, 3);
    painter.restore();
    painter.save();
    painter.setPen(minuteColor);
    for (int j = 0; j < 60; ++j) {
        if ((j % 5) != 0)
            painter.drawLine(92, 0, 96, 0);
        painter.rotate(6.0);
    }
    painter.restore();

    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(secondColor);
    painter.rotate(6.0 * (time.second() + time.msec() / 1000.0));
    painter.drawConvexPolygon(secondHand, 3);
    painter.restore();

    painter.save();
    painter.drawEllipse(-96, -96, 192, 192);
    painter.restore();
}

void AnalogClock::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == m_timerId)
        update();
}

