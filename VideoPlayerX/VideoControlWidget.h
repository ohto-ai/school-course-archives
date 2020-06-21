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

	void forword();
	void backword();
	void setMediaPlayer(QMediaPlayer*);

protected:
	friend class VideoPlayerX;
	QMediaPlayer* mediaPlayer{ nullptr };
	int fwbfStepLength{ 2000 }; // 快进快退步长

	virtual void keyPressEvent(QKeyEvent* event);
	virtual void mouseDoubleClickEvent(QMouseEvent* event);
};
