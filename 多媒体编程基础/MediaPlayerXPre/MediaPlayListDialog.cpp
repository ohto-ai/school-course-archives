#include "MediaPlayListDialog.h"
#include <thread>
#include <chrono>

MediaPlayListDialog::MediaPlayListDialog(QWidget*parent)
	: QDialog(parent)
{
	ui.setupUi(this);

	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
	ui.playListTableWidget->setColumnWidth(0, 320);
	ui.playListTableWidget->setColumnWidth(1, 60);
	ui.playListTableWidget->setColumnWidth(2, 50);

	connect(ui.playListTableWidget, &QTableWidget::cellDoubleClicked, [&](int row, int)
		{
			playList->setCurrentIndex(row);
			player->play();
		});


    connect(playList, &QMediaPlaylist::currentIndexChanged, [&](int index)
        {
            if (lastPlaylistIndex >= 0)
                ui.playListTableWidget->setVerticalHeaderItem(lastPlaylistIndex, new QTableWidgetItem(QString::asprintf("%d", lastPlaylistIndex + 1)));
            lastPlaylistIndex = index;
            ui.playListTableWidget->setVerticalHeaderItem(index, new QTableWidgetItem(QIcon(":/MediaPlayerXPre/res/music.png"), ""));
        });

    connect(ui.playListTableWidget, &QTableWidget::customContextMenuRequested, this, &MediaPlayListDialog::customContextMenuRequested);
}

MediaPlayListDialog::~MediaPlayListDialog()
{
}

void MediaPlayListDialog::addMedia(QString filePath)
{
	playList->addMedia(QUrl::fromLocalFile(filePath));
	ui.playListTableWidget->insertRow(ui.playListTableWidget->rowCount());
	ui.playListTableWidget->setItem(ui.playListTableWidget->rowCount() - 1, 0, new QTableWidgetItem(QFileInfo(filePath).completeBaseName()));
	ui.playListTableWidget->setItem(ui.playListTableWidget->rowCount() - 1, 2, new QTableWidgetItem(QFileInfo(filePath).suffix()));
}

void MediaPlayListDialog::customContextMenuRequested(const QPoint& pos)
{
    QMenu* pMenu = new QMenu(this);

    QAction* actionPlay = new QAction(QIcon(":/MediaPlayerXPre/res/music.png"), config::GlobalConfig["PlaylistDialog"]["CustomContextMenu"]["play"], this);
    QAction* actionLocate = new QAction(QIcon(":/MediaPlayerXPre/res/folder.png"), config::GlobalConfig["PlaylistDialog"]["CustomContextMenu"]["locate"], this);
    QAction* actionDelete = new QAction(QIcon(":/MediaPlayerXPre/res/remove.png"), config::GlobalConfig["PlaylistDialog"]["CustomContextMenu"]["remove"], this);
    QAction* actionClear = new QAction(QIcon(":/MediaPlayerXPre/res/clear.png"), config::GlobalConfig["PlaylistDialog"]["CustomContextMenu"]["clear"], this);

    actionPlay->setData(MediaPlayListDialog_Menu_Play);
    actionLocate->setData(MediaPlayListDialog_Menu_Locate);
    actionDelete->setData(MediaPlayListDialog_Menu_Delete);
    actionClear->setData(MediaPlayListDialog_Menu_Clear);

    pMenu->addAction(actionPlay);
    pMenu->addAction(actionLocate);
    pMenu->addAction(actionDelete);
    pMenu->addAction(actionClear);

    connect(actionPlay, &QAction::triggered, this, &MediaPlayListDialog::onTaskBoxContextMenuEvent);
    connect(actionLocate, &QAction::triggered, this, &MediaPlayListDialog::onTaskBoxContextMenuEvent);
    connect(actionDelete, &QAction::triggered, this, &MediaPlayListDialog::onTaskBoxContextMenuEvent);
    connect(actionClear, &QAction::triggered, this, &MediaPlayListDialog::onTaskBoxContextMenuEvent);

    pMenu->exec(cursor().pos());
}

void MediaPlayListDialog::onTaskBoxContextMenuEvent()
{
    switch (qobject_cast<QAction*>(this->sender())->data().toInt())
    {
    case MediaPlayListDialog_Menu_Play:
        playList->setCurrentIndex(ui.playListTableWidget->currentRow());
        player->play();
        break;
    case MediaPlayListDialog_Menu_Locate:
        QDesktopServices::openUrl(QFileInfo(playList->media(ui.playListTableWidget->currentRow()).canonicalUrl().toLocalFile()).path());
        break;
    case MediaPlayListDialog_Menu_Delete:
        playList->removeMedia(ui.playListTableWidget->currentRow());
        ui.playListTableWidget->removeRow(ui.playListTableWidget->currentRow());
        break;
    case MediaPlayListDialog_Menu_Clear:
        playList->clear();
        lastPlaylistIndex = -1;
        ui.playListTableWidget->clearContents();
        ui.playListTableWidget->setRowCount(0);
        break;
    default:
        break;
    }
}

void MediaPlayListDialog::setMediaPlayer(QMediaPlayer* player)
{
    this->player = player;
    player->setPlaylist(playList);
}

void MediaPlayListDialog::moveEvent(QMoveEvent* e)
{
    auto& configPlaylistDialog = config::GlobalConfig["PlaylistDialog"];
    configPlaylistDialog["x"] = x();
    configPlaylistDialog["y"] = y();
}

void MediaPlayListDialog::resizeEvent(QResizeEvent* e)
{
    auto& configPlaylistDialog = config::GlobalConfig["PlaylistDialog"];
    configPlaylistDialog["width"] = width();
    configPlaylistDialog["height"] = height();
}

void MediaPlayListDialog::loadMediaPlaylist()
{
    const auto& mediaList = config::GlobalConfig["Playlist"]["media_list"];
    ui.playListTableWidget->clearContents();
    ui.playListTableWidget->setRowCount(0);
    playList->clear();
    lastPlaylistIndex = -1;

    for (const auto& media : mediaList)
        addMedia(media);
    player->stop();
}

void MediaPlayListDialog::saveMediaPlaylist() const
{
    auto& mediaList = config::GlobalConfig["Playlist"]["media_list"];
    mediaList.clear();
    for (int index = 0; index < playList->mediaCount(); index++)
    {
        mediaList.push_back(playList->media(index).canonicalUrl().toLocalFile());
    }
}
