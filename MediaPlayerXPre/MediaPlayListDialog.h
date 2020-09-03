#pragma once

#include <QFileDialog>
#include <QDialog>
#include <QDesktopServices>
#include <QFileInfo>
#include <QMenu>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include "ui_MediaPlayListDialog.h"

class MediaPlayListDialog : public QDialog
{
	Q_OBJECT

public:
	friend class MediaPlayerXPre;
	MediaPlayListDialog(QWidget*parent = Q_NULLPTR);
	~MediaPlayListDialog();

	void addMedia(QString filePath);

protected:
	enum : uint { MediaPlayListDialog_Menu_Play
		, MediaPlayListDialog_Menu_Locate
		, MediaPlayListDialog_Menu_Delete
		, MediaPlayListDialog_Menu_Clear
	};

	void customContextMenuRequested(const QPoint& pos);
	void onTaskBoxContextMenuEvent();
	void setMediaPlayer(QMediaPlayer* player);
private:
	int lastPlaylistIndex = -1;
	QMediaPlayer* player;
	QMediaPlaylist playList;
	Ui::MediaPlayListDialog ui;
};
