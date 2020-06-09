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

void VideoControlWidget::setMediaPlayer(QMediaPlayer* player)
{
   mediaPlayer = player;
}

void VideoControlWidget::keyPressEvent(QKeyEvent* event)
{
    if (event->key() == Qt::Key_Escape && isFullScreen())
    {
        setFullScreen(false);
        event->accept();
        QVideoWidget::keyPressEvent(event);
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
