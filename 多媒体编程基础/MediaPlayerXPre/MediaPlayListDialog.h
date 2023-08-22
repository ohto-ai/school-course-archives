#pragma once

#include <QFileDialog>
#include <QDialog>
#include <QDesktopServices>
#include <QFileInfo>
#include <QMenu>
#include <QMediaPlaylist>
#include <QMediaPlayer>
#include "GlobalConfig.h"
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
	void moveEvent(QMoveEvent* e) override;
	void resizeEvent(QResizeEvent* e) override;

	void loadMediaPlaylist();
	void saveMediaPlaylist()const;
private:
	int lastPlaylistIndex = -1;

	QMediaPlayer* player;
	QMediaPlaylist* playList{ new QMediaPlaylist };
	Ui::MediaPlayListDialog ui;
};
