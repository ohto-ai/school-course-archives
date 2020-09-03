#include "MediaPlayerXPre.h"
#include <QKeyEvent>
// TODO: 截屏
// TODO: 窗口同步
// TODO: 播放列表同步 √
// TODO: 媒体信息显示 类型显示
// TODO: 字幕
// TODO: 列表的保存与读取
// TODO: 列表的删减 √



MediaPlayerXPre::MediaPlayerXPre(QWidget *parent)
    : QMainWindow(parent)
{
    try
    {
        setConfig();
    }
    catch (nlohmann::json::type_error e)
    {
        resetConfig();
        setConfig();
    }

    initMainwindowWidgets();
    initMediaPlayer();
    


}

void MediaPlayerXPre::setConfig()
{
    config::loadConfig();

    // 主窗口设置
    auto& configMainWindow = config::GlobalConfig["MainWindow"];
    move(configMainWindow["x"].get<int>(), configMainWindow["y"].get<int>());
    resize(configMainWindow["width"].get<int>(), configMainWindow["height"].get<int>());
    configMainWindow["tip_delay"].get_to<uint>(tipDelay);
}

void MediaPlayerXPre::resetConfig()
{
    auto& configMainWindow = config::GlobalConfig["MainWindow"];
    configMainWindow["x"] = 200;
    configMainWindow["y"] = 200;
    configMainWindow["width"] = 950;
    configMainWindow["height"] = 600;

    configMainWindow["tip_delay"] = 1500;

    config::saveConfig();
}

void MediaPlayerXPre::closeEvent(QCloseEvent* e)
{
    playListDialog.close();
    config::saveConfig();
}

void MediaPlayerXPre::resizeEvent(QResizeEvent* e)
{
    auto& configMainWindow = config::GlobalConfig["MainWindow"];
    configMainWindow["width"] = frameGeometry().width();
    configMainWindow["height"] = frameGeometry().height();
}

void MediaPlayerXPre::moveEvent(QMoveEvent* e)
{
    auto& configMainWindow = config::GlobalConfig["MainWindow"];
    configMainWindow["x"] = frameGeometry().x();
    configMainWindow["y"] = frameGeometry().y();
}

void MediaPlayerXPre::setScreenTip(QString tip)
{
    ui.tipLabel->setText(tip);
    ui.tipLabel->show();
    tipTimer.start(tipDelay);
}

void MediaPlayerXPre::initMainwindowWidgets()
{
    ui.setupUi(this);
    ui.pauseBtn->hide();
}

void MediaPlayerXPre::initMediaPlayer()
{
    player = new QMediaPlayer(this);
    player->setNotifyInterval(10);
    playListDialog.setMediaPlayer(player);
    ui.videoWidget->setMediaPlayer(player);
}

void MediaPlayerXPre::initSignals()
{
    // 定时器
    connect(&tipTimer, &QTimer::timeout, ui.tipLabel, &QLabel::hide);

    // 按钮状态切换
    connect(player, &QMediaPlayer::stateChanged, [&](QMediaPlayer::State state)
        {
            ui.pauseBtn->setHidden(state == QMediaPlayer::PausedState || state == QMediaPlayer::StoppedState);
            ui.playBtn->setHidden(state == QMediaPlayer::PlayingState);
            ui.stopBtn->setEnabled(state != QMediaPlayer::StoppedState);

            switch (state)
            {
            case QMediaPlayer::PausedState:
                setScreenTip("暂停");
                break;
            case QMediaPlayer::StoppedState:
                setScreenTip("停止");
                setWindowTitle("MediaPlayerXPre");
                break;
            case QMediaPlayer::PlayingState:
            {
                auto baseName{ QFileInfo(playListDialog.playList.currentMedia().canonicalUrl().toLocalFile()).baseName() };
                setScreenTip(baseName);
                setWindowTitle("MediaPlayerXPre - " + baseName);
            }
            break;
            }
        });

    // 进度控制
    connect(player, &QMediaPlayer::durationChanged, [&](qint64 duration)
        {
            ui.positionSlider->setMaximum(duration);
            int secs = duration / 1000;
            int hour = secs / 3600;
            int mins = (secs / 60) % 60;
            secs %= 60;
            durationTime = QString::asprintf("%02d:%02d:%02d", hour, mins, secs);
            ui.positionLab->setText(positionTime + "/" + durationTime);

            if (duration <= 0 || playListDialog.playList.isEmpty())
                return;
            auto item = playListDialog.ui.playListTableWidget->item(playListDialog.playList.currentIndex(), 1);
            if (item == nullptr)
                playListDialog.ui.playListTableWidget->setItem(playListDialog.playList.currentIndex(), 1, new QTableWidgetItem(durationTime));
            else
                item->setText(durationTime);

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
            {
                player->setPosition(value);

                int msec = value % 1000;
                int secs = value / 1000;
                int hour = secs / 3600;
                int mins = (secs / 60) % 60;
                secs %= 60;
                setScreenTip(QString::asprintf("进度：%02d:%02d:%02d.%03d(%.0lf%%)", hour, mins, secs, msec, (double)value / player->duration() * 100));
            }
        });

    connect(ui.volumeSlider, &QSlider::valueChanged, [&](int value)
        {
            if (value > 100)
                value = 100;
            if (value > 0)
                lastVolume = value;
            player->setVolume(value);
            player->setMuted(value <= 0);
            ui.volumeBtn->setIcon(QIcon(QString::asprintf(":/MediaPlayerXPre/res/player_voice_%d.png", (value * 16 + 99) / 100)));
            setScreenTip(QString::asprintf(value <= 0 ? "静音" : "音量：%d%%", value));
        });
    connect(ui.volumeBtn, &QPushButton::clicked, [&]
        {
            player->setMuted(!player->isMuted());
            ui.volumeSlider->setValue(player->isMuted() ? 0 : lastVolume);
        });

    // 文件打开
    connect(ui.openBtn, &TBPushButton::leftClicked, [&]
        {
            QStringList filePaths;


            filePaths = QFileDialog::getOpenFileNames(this, "Open", ""
                , "Supported file types(*.mp3;*.wav;*.wma;*.ogg;*.acc;*.flac;*.wmv;*.avi;*.mp4;*.mpeg;*.mkv;*.rmvb;*.flv;*.3gp);;\
Videos(*.wmv;*.avi;*.mp4;*.mpeg;*.mkv;*.rmvb;*.flv;*.3gp);;\
Sounds(*.mp3;*.wav;*.wma;*.ogg;*.acc;*.flac);;\
Any(*.*)");

            if (filePaths.empty())
                return;
            for (const auto& mediaFile : filePaths)
                playListDialog.addMedia(mediaFile);
            playListDialog.playList.setCurrentIndex(playListDialog.playList.mediaCount() - filePaths.size() - 1);
            player->play();
        });
    connect(ui.openBtn, &TBPushButton::rightClicked, [&]
        {
            auto dir = QDir(QFileDialog::getExistingDirectory(this, "Open", ""));
            dir.setFilter(QDir::Files | QDir::NoSymLinks);
            auto fileInfoList = dir.entryInfoList({ "*.mp3", "*.wav", "*.wma", "*.ogg", "*.acc", "*.flac", "*.3gp"
                , "*.wmv", "*.avi", "*.mp4", "*.mpeg", "*.mkv", "*.rmvb", "*.flv" });

            if (fileInfoList.empty())
                return;
            for (const auto& mediaFileInfo : fileInfoList)
                playListDialog.addMedia(mediaFileInfo.absoluteFilePath());

            playListDialog.playList.setCurrentIndex(playListDialog.playList.mediaCount() - fileInfoList.size() - 1);
            player->play();
        });

    // 播放控制
    connect(ui.playBtn, &QPushButton::clicked, player, &QMediaPlayer::play);
    connect(ui.pauseBtn, &QPushButton::clicked, player, &QMediaPlayer::pause);
    connect(ui.stopBtn, &QPushButton::clicked, player, &QMediaPlayer::stop);

    connect(ui.leftBtn, &TBPushButton::leftClicked, [&]
        {
            ui.videoWidget->backword();
            setScreenTip(QString::asprintf("快退 %.3f(%.0lf%%)", ui.videoWidget->fwbfStepLength() / 1000.0, (double)player->position() / player->duration() * 100));
        });
    connect(ui.rightBtn, &TBPushButton::leftClicked, [&]
        {
            ui.videoWidget->forword();
            setScreenTip(QString::asprintf("快进 %.3f(%.0lf%%)", ui.videoWidget->fwbfStepLength() / 1000.0, (double)player->position() / player->duration() * 100));
        });
    connect(ui.leftBtn, &TBPushButton::rightClicked, &playListDialog.playList, &QMediaPlaylist::previous);
    connect(ui.rightBtn, &TBPushButton::rightClicked, &playListDialog.playList, &QMediaPlaylist::next);

    // 全屏
    connect(ui.fullscreenBtn, &QPushButton::clicked, [&] {ui.videoWidget->setFullScreen(true); });

    // 循环状态
    connect(ui.playbackModePushButton, &TBPushButton::leftClicked, [&]
        {
            switch (playListDialog.playList.playbackMode())
            {
            case QMediaPlaylist::PlaybackMode::CurrentItemInLoop:
                playListDialog.playList.setPlaybackMode(QMediaPlaylist::PlaybackMode::Sequential);
                break;
            case QMediaPlaylist::PlaybackMode::Sequential:
                playListDialog.playList.setPlaybackMode(QMediaPlaylist::PlaybackMode::Loop);
                break;
            case QMediaPlaylist::PlaybackMode::Loop:
                playListDialog.playList.setPlaybackMode(QMediaPlaylist::PlaybackMode::Random);
                break;
            case QMediaPlaylist::PlaybackMode::Random:
                playListDialog.playList.setPlaybackMode(QMediaPlaylist::PlaybackMode::CurrentItemInLoop);
                break;
            default:
                playListDialog.playList.setPlaybackMode(QMediaPlaylist::PlaybackMode::Sequential);
                break;
            }

        });
    connect(ui.playbackModePushButton, &TBPushButton::rightClicked, [&]
        {
            switch (playListDialog.playList.playbackMode())
            {
            case QMediaPlaylist::PlaybackMode::CurrentItemInLoop:
                playListDialog.playList.setPlaybackMode(QMediaPlaylist::PlaybackMode::Random);
                break;
            case QMediaPlaylist::PlaybackMode::Sequential:
                playListDialog.playList.setPlaybackMode(QMediaPlaylist::PlaybackMode::CurrentItemInLoop);
                break;
            case QMediaPlaylist::PlaybackMode::Loop:
                playListDialog.playList.setPlaybackMode(QMediaPlaylist::PlaybackMode::Sequential);
                break;
            case QMediaPlaylist::PlaybackMode::Random:
                playListDialog.playList.setPlaybackMode(QMediaPlaylist::PlaybackMode::Loop);
                break;
            default:
                playListDialog.playList.setPlaybackMode(QMediaPlaylist::PlaybackMode::Sequential);
                break;
            }

        });
    connect(&playListDialog.playList, &QMediaPlaylist::playbackModeChanged, [&]
        {
            switch (playListDialog.playList.playbackMode())
            {
            case QMediaPlaylist::PlaybackMode::CurrentItemInLoop:
                ui.playbackModePushButton->setIcon(QIcon(":/MediaPlayerXPre/res/currentiteminloop.png"));
                setScreenTip("单曲循环");
                ui.playbackModePushButton->setToolTip("单曲循环");
                break;
            case QMediaPlaylist::PlaybackMode::Sequential:
                ui.playbackModePushButton->setIcon(QIcon(":/MediaPlayerXPre/res/sequential.png"));
                setScreenTip("顺序播放");
                ui.playbackModePushButton->setToolTip("顺序播放");
                break;
            case QMediaPlaylist::PlaybackMode::Loop:
                ui.playbackModePushButton->setIcon(QIcon(":/MediaPlayerXPre/res/loop.png"));
                setScreenTip("列表循环");
                ui.playbackModePushButton->setToolTip("列表循环");
                break;
            case QMediaPlaylist::PlaybackMode::Random:
                ui.playbackModePushButton->setIcon(QIcon(":/MediaPlayerXPre/res/random.png"));
                setScreenTip("随机播放");
                ui.playbackModePushButton->setToolTip("随机播放");
                break;
            default:
                playListDialog.playList.setPlaybackMode(QMediaPlaylist::PlaybackMode::Sequential);
                break;
            }
        });
    connect(&playListDialog.playList, &QMediaPlaylist::currentIndexChanged, [&](int index)
        {
            setScreenTip(QFileInfo(playListDialog.playList.currentMedia().canonicalUrl().toLocalFile()).fileName());
            setWindowTitle("MediaPlayerXPre - " + QFileInfo(playListDialog.playList.currentMedia().canonicalUrl().toLocalFile()).baseName());
        });


    // 视频设置
    connect(ui.optionButton, &QPushButton::clicked, [&]
        {
            if (optionDialog.isVisible())
                optionDialog.hide();
            else
                optionDialog.show();
            setScreenTip(QString::asprintf("视频设置：%s", optionDialog.isVisible() ? "显示" : "隐藏"));
        });

    connect(optionDialog.ui.brightnessSlider, &QSlider::valueChanged, [&](int value)
        {
            ui.videoWidget->setBrightness(value);
            setScreenTip(QString::asprintf("亮度 %+d%%", value));
        });
    connect(optionDialog.ui.contrastSlider, &QSlider::valueChanged, [&](int value)
        {
            ui.videoWidget->setContrast(value);
            setScreenTip(QString::asprintf("对比度 %+d%%", value));
        });
    connect(optionDialog.ui.hueSlider, &QSlider::valueChanged, [&](int value)
        {
            ui.videoWidget->setHue(value);
            setScreenTip(QString::asprintf("色相 %+d%%", value));
        });
    connect(optionDialog.ui.saturationSlider, &QSlider::valueChanged, [&](int value)
        {
            ui.videoWidget->setSaturation(value);
            setScreenTip(QString::asprintf("饱和度 %+d%%", value));
        });
    connect(optionDialog.ui.brightnessDefaultBtn, &QPushButton::clicked, [&] {optionDialog.ui.brightnessSlider->setValue(0); });
    connect(optionDialog.ui.contrastDefaultBtn, &QPushButton::clicked, [&] {optionDialog.ui.contrastSlider->setValue(0); });
    connect(optionDialog.ui.hueDefaultBtn, &QPushButton::clicked, [&] {optionDialog.ui.hueSlider->setValue(0); });
    connect(optionDialog.ui.saturationDefaultBtn, &QPushButton::clicked, [&] {optionDialog.ui.saturationSlider->setValue(0); });

    // 播放列表
    connect(ui.playListButton, &QPushButton::clicked, [&]
        {
            if (playListDialog.isVisible())
                playListDialog.hide();
            else
                playListDialog.show();
            setScreenTip(QString::asprintf("播放列表：%s", playListDialog.isVisible() ? "显示" : "隐藏"));
        });
}
