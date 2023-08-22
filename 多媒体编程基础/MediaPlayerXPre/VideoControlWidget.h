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
	void setfwbfStepLength(int);
	int fwbfStepLength()const;

protected:
	friend class MediaPlayerXPre;
	QMediaPlayer* mediaPlayer{ nullptr };
	int m_fwbfStepLength{ 2000 }; // forword/backword step

	virtual void keyPressEvent(QKeyEvent* event);
	virtual void mouseDoubleClickEvent(QMouseEvent* event);
};
