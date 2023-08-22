#include "DigitalClockX.h"

DigitalClockX::DigitalClockX(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    QImage image;
    image.load(":/DigitalClockX/res/digital.png");
    background.load(":/DigitalClockX/res/bk.jpg");
    digitalWidth = image.width() / 11;
    digitalHeight = image.height();
    for (size_t i = 0; i < 11; i++)
        digitalImages[i] = image.copy(digitalWidth * i, 0, digitalWidth, digitalHeight);
    freshTimer = startTimer(10);
}

void DigitalClockX::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setBackgroundMode(Qt::BGMode::TransparentMode);
    painter.drawImage(0, 0, background);
    paintClock(painter);
}

void DigitalClockX::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == freshTimer)
        update();
}

void DigitalClockX::paintClock(QPainter& painter)
{
    QTime time = QTime::currentTime();

    painter.drawImage(digitalWidth * 0, 0, digitalImages[time.hour() / 10]);
    painter.drawImage(digitalWidth * 1, 0, digitalImages[time.hour() % 10]);

    painter.drawImage(digitalWidth * 2, 0, digitalImages[10]);

    painter.drawImage(digitalWidth * 3, 0, digitalImages[time.minute() / 10]);
    painter.drawImage(digitalWidth * 4, 0, digitalImages[time.minute() % 10]);

    painter.drawImage(digitalWidth * 5, 0, digitalImages[10]);

    painter.drawImage(digitalWidth * 6, 0, digitalImages[time.second() / 10]);
    painter.drawImage(digitalWidth * 7, 0, digitalImages[time.second() % 10]);

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
    QColor minuteColor(202, 81, 0, 191);
    QColor secondColor(240, 40, 40, 240);

    painter.setRenderHint(QPainter::Antialiasing);
    int availableWidth = width();
    int availableHeight = height() - digitalHeight;
    painter.translate(availableWidth / 2, availableHeight / 2 + digitalHeight);

    int side = qMin(availableWidth, availableHeight);
    painter.scale(side / 200.0, side / 200.0);


    painter.save();
    painter.setBrush(QColor(240, 240, 240, 127));
    painter.drawEllipse(-96, -96, 192, 192);
    painter.restore();

    painter.save();
    painter.setPen(Qt::NoPen);
    painter.setBrush(hourColor);
    painter.rotate(30.0 * ((time.hour() + time.minute() / 60.0)));
    painter.drawConvexPolygon(hourHand, 3);
    painter.restore();

    painter.save();
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
