#pragma once

#include <QtWidgets/QMainWindow>
#include <QGraphicsVideoItem>
#include <QGraphicsTextItem>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QMediaPlayer>
#include <QMediaPlayList>
#include <QFileDialog>
#include <QTimer>
#include "TBPushButton.h"
#include <MediaPlayListDialog.h>
#include "VideoControlWidget.h"
#include "AuthorInformation.h"
#include "OptionDialog.h"
#include "GlobalConfig.h"
#include "ui_MediaPlayerXPre.h"

class MediaPlayerXPre : public QMainWindow
{
    Q_OBJECT

public:
    MediaPlayerXPre(QWidget *parent = Q_NULLPTR);

protected:
    void closeEvent(QCloseEvent* e) override;
    void resizeEvent(QResizeEvent* e) override;
    void moveEvent(QMoveEvent* e) override;
private:
    friend class MultiMediaSystem;

    Ui::MediaPlayerXPreClass ui;

    void setScreenTip(QString tip);
    void initMediaPlayer();
    void initSignals();


    QTimer tipTimer;
    uint tipDelay{ 1500u };

    QMediaPlayer* player{ nullptr };
    QString durationTime{ "00:00:00" };
    QString positionTime{ "00:00:00" };
    OptionDialog optionDialog{ this };
    MediaPlayListDialog playListDialog;
    AuthorInformation authorInformation{ this };

    bool isPlayingBeforeTurnBackground{ false };
    bool isTurnBackground{ false };
    int lastVolume = 100;
};
