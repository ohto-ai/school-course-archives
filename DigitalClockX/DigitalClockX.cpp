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

    setFixedSize(background.width(), background.height());
    freshTimer = startTimer(100);
}

void DigitalClockX::paintEvent(QPaintEvent*)
{
    QPainter painter(this);
    painter.setBackgroundMode(Qt::BGMode::TransparentMode);
    QTime current_time = QTime::currentTime();

    painter.drawImage(0, 0, background);
    paintClock(painter, current_time.hour(), current_time.minute(), current_time.second());
}

void DigitalClockX::timerEvent(QTimerEvent* event)
{
    if (event->timerId() == freshTimer)
        update();
}

void DigitalClockX::paintClock(QPainter& painter, int h, int m, int s)
{
    painter.drawImage(digitalWidth * 0, 0, digitalImages[h / 10]);
    painter.drawImage(digitalWidth * 1, 0, digitalImages[h % 10]);

    painter.drawImage(digitalWidth * 2, 0, digitalImages[10]);

    painter.drawImage(digitalWidth * 3, 0, digitalImages[m / 10]);
    painter.drawImage(digitalWidth * 4, 0, digitalImages[m % 10]);

    painter.drawImage(digitalWidth * 5, 0, digitalImages[10]);

    painter.drawImage(digitalWidth * 6, 0, digitalImages[s / 10]);
    painter.drawImage(digitalWidth * 7, 0, digitalImages[s % 10]);
}
