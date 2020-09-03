#include "MediaPlayListDialog.h"

MediaPlayListDialog::MediaPlayListDialog(QWidget*parent)
	: QDialog(parent)
{
	ui.setupUi(this);
	setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowCloseButtonHint);
	ui.playListTableWidget->setColumnWidth(0, 320);
	ui.playListTableWidget->setColumnWidth(1, 100);
	playList.setPlaybackMode(QMediaPlaylist::PlaybackMode::Sequential);

	connect(ui.playListTableWidget, &QTableWidget::cellDoubleClicked, [&](int row, int)
		{
			playList.setCurrentIndex(row);
			player->play();
		});


    connect(&playList, &QMediaPlaylist::currentIndexChanged, [&](int index)
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
	playList.addMedia(QMediaContent(QUrl::fromLocalFile(filePath)));
	ui.playListTableWidget->insertRow(ui.playListTableWidget->rowCount());
	ui.playListTableWidget->setItem(ui.playListTableWidget->rowCount() - 1, 0, new QTableWidgetItem(QFileInfo(filePath).baseName()));
}

void MediaPlayListDialog::customContextMenuRequested(const QPoint& pos)
{
    QMenu* pMenu = new QMenu(this);

    QAction* actionPlay = new QAction("Play", this);
    QAction* actionLocate = new QAction("Locate the file", this);
    QAction* actionDelete = new QAction("Remove from the list", this);
    QAction* actionClear = new QAction("Clear the list", this);

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
        playList.setCurrentIndex(ui.playListTableWidget->currentRow());
        player->play();
        break;
    case MediaPlayListDialog_Menu_Locate:
        QDesktopServices::openUrl(QFileInfo(playList.media(ui.playListTableWidget->currentRow()).canonicalUrl().toLocalFile()).path());
        break;
    case MediaPlayListDialog_Menu_Delete:
        playList.removeMedia(ui.playListTableWidget->currentRow());
        ui.playListTableWidget->removeRow(ui.playListTableWidget->currentRow());
        break;
    case MediaPlayListDialog_Menu_Clear:
        playList.clear();
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
    player->setPlaylist(&playList);
}
