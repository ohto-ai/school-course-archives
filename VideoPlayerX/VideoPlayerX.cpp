#include "VideoPlayerX.h"
#include <QKeyEvent>

VideoPlayerX::VideoPlayerX(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    player = new QMediaPlayer(this);
    player->setNotifyInterval(10);
    player->setVideoOutput(ui.videoWidget);
    ui.videoWidget->setMediaPlayer(player);
    ui.pauseBtn->hide();
    optionDialog.setWindowTitle("视频设置");
    optionDialog.setWindowIcon(QIcon(":/VideoPlayerX/res/player.ico"));
    setWindowIcon(QIcon(":/VideoPlayerX/res/player.ico"));

    connect(player, &QMediaPlayer::stateChanged, [&](QMediaPlayer::State state)
        {
            ui.pauseBtn->setHidden(state == QMediaPlayer::PausedState || state == QMediaPlayer::StoppedState);
            ui.playBtn->setHidden(state == QMediaPlayer::PlayingState);
            ui.stopBtn->setEnabled(state != QMediaPlayer::StoppedState);
        });
    connect(player, &QMediaPlayer::durationChanged, [&](qint64 duration)
        {
            ui.positionSlider->setMaximum(duration);
            int secs = duration / 1000;
            int hour = secs / 3600;
            int mins = (secs / 60) % 60;
            secs %= 60;
            durationTime = QString::asprintf("%02d:%02d:%02d", hour, mins, secs);
            ui.positionLab->setText(positionTime + "/" + durationTime);
        });
    connect(player, &QMediaPlayer::positionChanged, [&](qint64 position)
        {
            if (!ui.positionSlider->isSliderDown())
                ui.positionSlider->setSliderPosition(position);

            int secs = position / 1000;
            int hour = secs / 3600;
            int mins = (secs / 60) % 60;
            secs %= 60;
            positionTime = QString::asprintf("%02d:%02d:%02d", hour, mins, secs);
            ui.positionLab->setText(positionTime + "/" + durationTime);
        });
    connect(ui.positionSlider, &QSlider::valueChanged, [&](int value)
        {
            if (ui.positionSlider->isSliderDown())
                player->setPosition(value);
        });


    connect(ui.volumeSlider, &QSlider::valueChanged, [&](int value)
        {
            if (value > 0)
                lastVolume = value;
            player->setVolume(value);
            player->setMuted(value <= 0);
            ui.volumeBtn->setIcon(QIcon(QString::asprintf(":/VideoPlayerX/res/player_voice_%d.png", (value * 16 + 99) / 100)));
        });
    connect(ui.volumeBtn, &QPushButton::clicked, [&]
        {
            player->setMuted(!player->isMuted());
            ui.volumeSlider->setValue(player->isMuted() ? 0 : lastVolume);
        });

    connect(ui.openBtn, &QPushButton::clicked, [&]
        {
            QString aFile = QFileDialog::getOpenFileName(this, "打开", ""
                , "支持的全部文件(*.mp3;*.wav;*.wma;*.ogg;*.acc;*.flac;*.wmv;*.avi;*.mp4;*.mpeg;*.mkv;*.rmvb;*.flv);;\
视频文件(*.wmv;*.avi;*.mp4;*.mpeg;*.mkv;*.rmvb;*.flv);;\
音频文件(*.mp3;*.wav;*.wma;*.ogg;*.acc;*.flac;*.wmv;*.avi;*.mp4;*.mpeg;*.mkv;*.rmvb;*.flv);;\
所有文件(*.*)");

            if (aFile.isEmpty())
                return;

            QFileInfo fileInfo(aFile);
            setWindowTitle("VideoPlayerX - " + fileInfo.fileName());
            player->setMedia(QUrl::fromLocalFile(aFile));
            player->play();
        });
    connect(ui.playBtn, &QPushButton::clicked, player, &QMediaPlayer::play);
    connect(ui.pauseBtn, &QPushButton::clicked, player, &QMediaPlayer::pause);
    connect(ui.stopBtn, &QPushButton::clicked, player, &QMediaPlayer::stop);
    connect(ui.leftBtn, &QPushButton::clicked, [&]
        {
            auto new_postion = player->position() - 2000;
            if (new_postion < 0)
                new_postion = 0;
            player->setPosition(new_postion);
        });
    connect(ui.rightBtn, &QPushButton::clicked, [&]
        {
            auto new_postion = player->position() + 2000;
            if (new_postion > player->duration())
                new_postion = player->duration();
            player->setPosition(new_postion);
        });
    connect(ui.fullscreenBtn, &QPushButton::clicked, [&] {ui.videoWidget->setFullScreen(true); });

    connect(ui.optionButton, &QPushButton::clicked, &optionDialog, &OptionDialog::show);
    connect(optionDialog.ui.brightnessSlider, &QSlider::valueChanged, ui.videoWidget, &QVideoWidget::setBrightness);
    connect(optionDialog.ui.contrastSlider, &QSlider::valueChanged, ui.videoWidget, &QVideoWidget::setContrast);
    connect(optionDialog.ui.hueSlider, &QSlider::valueChanged, ui.videoWidget, &QVideoWidget::setHue);
    connect(optionDialog.ui.saturationSlider, &QSlider::valueChanged, ui.videoWidget, &QVideoWidget::setSaturation);
    connect(optionDialog.ui.brightnessDefaultBtn, &QPushButton::clicked, [&] {optionDialog.ui.brightnessSlider->setValue(0); });
    connect(optionDialog.ui.contrastDefaultBtn, &QPushButton::clicked, [&] {optionDialog.ui.contrastSlider->setValue(0); });
    connect(optionDialog.ui.hueDefaultBtn, &QPushButton::clicked, [&] {optionDialog.ui.hueSlider->setValue(0); });
    connect(optionDialog.ui.saturationDefaultBtn, &QPushButton::clicked, [&] {optionDialog.ui.saturationSlider->setValue(0); });
}

void VideoPlayerX::turnBackground()
{
    if (isTurnBackground)
        return;
    isTurnBackground = true;
    if (ui.btnPlayBack->isChecked())
        return;
    isPlayingBeforeTurnBackground = player->state() == QMediaPlayer::PlayingState;
    if (isPlayingBeforeTurnBackground)
        player->pause();
}

void VideoPlayerX::turnForeground()
{
    isTurnBackground = false;
    if (isPlayingBeforeTurnBackground)
        player->play();
}
