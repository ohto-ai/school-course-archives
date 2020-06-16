#pragma once

#include <QVideoWidget>
#include <QMediaPlayer>
#ifdef Q_OS_WIN
#pragma execution_character_set("utf-8")
#endif

class VideoControlWidget : public QVideoWidget
{
	Q_OBJECT

public:
	VideoControlWidget(QWidget *parent);
	~VideoControlWidget();

	void setMediaPlayer(QMediaPlayer*);

protected:
	QMediaPlayer* mediaPlayer{ nullptr };

	virtual void keyPressEvent(QKeyEvent* event);
	virtual void mouseDoubleClickEvent(QMouseEvent* event);
};
