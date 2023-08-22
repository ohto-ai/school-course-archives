#pragma once

#include <QtWidgets/QMainWindow>
#include <QMediaPlayer>
#include <QFileDialog>
#include "VideoControlWidget.h"
#include "OptionDialog.h"
#include "ui_VideoPlayerX.h"

class VideoPlayerX : public QMainWindow
{
    Q_OBJECT

public:
    VideoPlayerX(QWidget *parent = Q_NULLPTR);

    void turnBackground();
    void turnForeground();
private:
    friend class MultiMediaSystem;

    Ui::VideoPlayerXClass ui;
    QMediaPlayer* player{ nullptr };
    QString durationTime{ "00:00:00" };
    QString positionTime{ "00:00:00" };
    OptionDialog optionDialog{ this };
    bool isPlayingBeforeTurnBackground{ false };
    bool isTurnBackground{ false };
    int lastVolume = 100;
};
