#include "VideoControlWidget.h"
#include <QKeyEvent>
#include <QMouseEvent>

VideoControlWidget::VideoControlWidget(QWidget *parent)
	: QVideoWidget(parent)
{
	
}

VideoControlWidget::~VideoControlWidget()
{
}

void VideoControlWidget::forword()
{
    if (mediaPlayer == nullptr)
        return;
    auto new_postion = mediaPlayer->position() + fwbfStepLength;
    if (new_postion > mediaPlayer->duration())
        new_postion = mediaPlayer->duration();
    mediaPlayer->setPosition(new_postion);
}

void VideoControlWidget::backword()
{
    if (mediaPlayer == nullptr)
        return;
    auto new_postion = mediaPlayer->position() - fwbfStepLength;
    if (new_postion < 0)
        new_postion = 0;
    mediaPlayer->setPosition(new_postion);
}

void VideoControlWidget::setMediaPlayer(QMediaPlayer* player)
{
   mediaPlayer = player;
}

void VideoControlWidget::keyPressEvent(QKeyEvent* event)
{
    switch (event->key())
    {
    case Qt::Key_Escape:
        if (isFullScreen()) {
            setFullScreen(false);
            event->accept();
        }
        break;
    case Qt::Key_Enter:
        setFullScreen(!isFullScreen());
        event->accept();
        break;
    case Qt::Key_Left:
        backword();
        event->accept();
        break;
    case Qt::Key_Right:
        forword();
        event->accept();
        break;
    case Qt::Key_Space:
        if (mediaPlayer == nullptr)
            break;
        if (mediaPlayer->state() == QMediaPlayer::PlayingState)
            mediaPlayer->pause();
        else
            mediaPlayer->play();
        event->accept();
        break;

    default:
        QVideoWidget::keyPressEvent(event);
        break;
    }
}

void VideoControlWidget::mouseDoubleClickEvent(QMouseEvent* event)
{
    if (event->button() == Qt::LeftButton)
    {
        if (mediaPlayer->state() == QMediaPlayer::PlayingState)
            mediaPlayer->pause();
        else
            mediaPlayer->play();
    }
    QVideoWidget::mouseDoubleClickEvent(event);
}
