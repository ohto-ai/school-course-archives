#include "MediaPlayerXPre.h"
#include <QKeyEvent>
// TODO: 截屏
// TODO: 窗口同步 ×
// TODO: 播放列表同步 √
// TODO: 媒体信息显示 √ 类型显示
// TODO: 字幕
// TODO: 列表的保存与读取 √
// TODO: 列表的删减 √


void from_json(const nlohmann::json& j, QString& s)
{
    s = QString::fromStdString(j.get<std::string>());
}

void from_json(const nlohmann::json& j, QMediaPlaylist::PlaybackMode& m)
{
    if (j == "CurrentItemOnce")
        m = QMediaPlaylist::PlaybackMode::CurrentItemOnce;
    else if (j == "CurrentItemInLoop")
        m = QMediaPlaylist::PlaybackMode::CurrentItemInLoop;
    else if (j == "Sequential")
        m = QMediaPlaylist::PlaybackMode::Sequential;
    else if (j == "Loop")
        m = QMediaPlaylist::PlaybackMode::Loop;
    else if (j == "Random")
        m = QMediaPlaylist::PlaybackMode::Random;
    else
        m = QMediaPlaylist::PlaybackMode::Sequential;

}

void to_json(nlohmann::json& j, const QString& s)
{
    j = s.toStdString();
}

void to_json(nlohmann::json& j, const QMediaPlaylist::PlaybackMode& m)
{
    switch (m)
    {
    case QMediaPlaylist::PlaybackMode::CurrentItemInLoop:
        j = "CurrentItemInLoop";
        break;
    case QMediaPlaylist::PlaybackMode::Sequential:
        j = "Sequential";
        break;
    case QMediaPlaylist::PlaybackMode::Loop:
        j = "Loop";
        break;
    case QMediaPlaylist::PlaybackMode::Random:
        j = "Random";
        break;
    case QMediaPlaylist::PlaybackMode::CurrentItemOnce:
    default:
        j = "CurrentItemOnce";
        break;
    }
}

MediaPlayerXPre::MediaPlayerXPre(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
    
    initMediaPlayer();
    initSignals();

    // 主窗口设置
    auto& configMainWindow = config::GlobalConfig["MainWindow"];
    move(configMainWindow["x"], configMainWindow["y"]);
    resize(configMainWindow["width"], configMainWindow["height"]);

    // 子窗口
    auto& configPlaylistDialog = config::GlobalConfig["PlaylistDialog"];
    playListDialog.move(configPlaylistDialog["x"], configPlaylistDialog["y"]);
    playListDialog.resize(configPlaylistDialog["width"], configPlaylistDialog["height"]);
    playListDialog.setWindowTitle(configPlaylistDialog["caption"]);

    auto& configOptionDialog = config::GlobalConfig["OptionDialog"];
    optionDialog.move(configOptionDialog["x"], configOptionDialog["y"]);
    optionDialog.resize(configOptionDialog["width"], configOptionDialog["height"]);
    optionDialog.setWindowTitle(configOptionDialog["caption"]);

    optionDialog.ui.brightnessSlider->setValue(config::GlobalConfig["VideoOption"]["brightness"]);
    optionDialog.ui.contrastSlider->setValue(config::GlobalConfig["VideoOption"]["contrast"]);
    optionDialog.ui.hueSlider->setValue(config::GlobalConfig["VideoOption"]["hue"]);
    optionDialog.ui.saturationSlider->setValue(config::GlobalConfig["VideoOption"]["saturation"]);

    ui.volumeSlider->setValue(config::GlobalConfig["Player"]["volume"]);
    playListDialog.playList->setPlaybackMode(config::GlobalConfig["Player"]["playback_mode"]);

    ui.pauseBtn->hide();

    // 播放列表
    playListDialog.loadMediaPlaylist();

    setScreenTip(QString::asprintf(config::GlobalConfig["ScreenTip"]["medias_loaded"].get<std::string>().c_str(), config::GlobalConfig["Playlist"]["media_list"].size()));
}

void MediaPlayerXPre::closeEvent(QCloseEvent* e)
{
    playListDialog.close();
    playListDialog.saveMediaPlaylist();
    config::saveConfig();
}

void MediaPlayerXPre::resizeEvent(QResizeEvent* e)
{
    auto& configMainWindow = config::GlobalConfig["MainWindow"];
    configMainWindow["width"] = width();
    configMainWindow["height"] = height();
}

void MediaPlayerXPre::moveEvent(QMoveEvent* e)
{
    auto& configMainWindow = config::GlobalConfig["MainWindow"];
    configMainWindow["x"] = x();
    configMainWindow["y"] = y();
}

void MediaPlayerXPre::setScreenTip(QString tip)
{
    ui.tipLabel->setText(tip);
    ui.tipLabel->show();
    tipTimer.start(tipDelay);
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
    using config::GlobalConfig;
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
                setScreenTip(GlobalConfig["ScreenTip"]["pause"]);
                break;
            case QMediaPlayer::StoppedState:
                setScreenTip(GlobalConfig["ScreenTip"]["stop"]);
                setWindowTitle("MediaPlayerXPre");
                break;
            case QMediaPlayer::PlayingState:
            {
                auto completeBaseName{ QFileInfo(playListDialog.playList->currentMedia().canonicalUrl().toLocalFile()).completeBaseName() };
                setScreenTip(completeBaseName);
                setWindowTitle("MediaPlayerXPre - " + completeBaseName);
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

            if (duration <= 0 || playListDialog.playList->isEmpty())
                return;
            auto item = playListDialog.ui.playListTableWidget->item(playListDialog.playList->currentIndex(), 1);
            if (item == nullptr)
                playListDialog.ui.playListTableWidget->setItem(playListDialog.playList->currentIndex(), 1, new QTableWidgetItem(durationTime));
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
                setScreenTip(GlobalConfig["ScreenTip"]["position"].get<QString>()+ QString::asprintf(": %02d:%02d:%02d.%03d(%.0lf%%)", hour, mins, secs, msec, (double)value / player->duration() * 100));
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
            setScreenTip(value <= 0 ? GlobalConfig["ScreenTip"]["muted"] : GlobalConfig["ScreenTip"]["volume"].get<QString>() + QString::asprintf(": %d%%", value));
        });
    connect(ui.volumeBtn, &QPushButton::clicked, [&]
        {
            player->setMuted(!player->isMuted());
            ui.volumeSlider->setValue(player->isMuted() ? 0 : lastVolume);
        });
    connect(player, &QMediaPlayer::volumeChanged, [&](int volume)
        {
            config::GlobalConfig["Player"]["volume"] = volume;
        });

    // 文件打开
    connect(ui.openBtn, &TBPushButton::leftClicked, [&]
        {
            QStringList filePaths;


            filePaths = QFileDialog::getOpenFileNames(this, config::GlobalConfig["Player"]["ImportFiles"]["caption"]
                , "", config::GlobalConfig["Player"]["ImportFiles"]["filter"]);

            if (filePaths.empty())
                return;
            for (const auto& mediaFile : filePaths)
                playListDialog.addMedia(mediaFile);
            playListDialog.playList->setCurrentIndex(playListDialog.playList->mediaCount() - filePaths.size());
            playListDialog.saveMediaPlaylist();
            player->play();
        });
    connect(ui.openBtn, &TBPushButton::rightClicked, [&]
        {
            QStringList list;
            const auto& nameFilters{ config::GlobalConfig["Player"]["ImportDirectory"]["name_filters"] };
            for (const auto& item : nameFilters)
                list.push_back(item);
            auto dirString = QFileDialog::getExistingDirectory(this, config::GlobalConfig["Player"]["ImportDirectory"]["caption"]);
            if (dirString.isEmpty())
                return;
            auto dir = QDir(dirString);
            dir.setFilter(QDir::Files | QDir::NoSymLinks);
            dir.setNameFilters(list);
            auto fileInfoList = dir.entryInfoList(list);

            if (fileInfoList.empty())
                return;
            for (const auto& mediaFileInfo : fileInfoList)
                playListDialog.addMedia(mediaFileInfo.absoluteFilePath());

            playListDialog.playList->setCurrentIndex(playListDialog.playList->mediaCount() - fileInfoList.size());
            playListDialog.saveMediaPlaylist();
            player->play();
        });

    // 播放控制
    connect(ui.playBtn, &QPushButton::clicked, player, &QMediaPlayer::play);
    connect(ui.pauseBtn, &QPushButton::clicked, player, &QMediaPlayer::pause);
    connect(ui.stopBtn, &QPushButton::clicked, player, &QMediaPlayer::stop);

    connect(ui.leftBtn, &TBPushButton::leftClicked, [&]
        {
            ui.videoWidget->backword();
            setScreenTip(QString::asprintf(config::GlobalConfig["ScreenTip"]["backword_tip"].get<std::string>().c_str(), ui.videoWidget->fwbfStepLength() / 1000.0, (double)player->position() / player->duration() * 100));
        });
    connect(ui.rightBtn, &TBPushButton::leftClicked, [&]
        {
            ui.videoWidget->forword();
            setScreenTip(QString::asprintf(config::GlobalConfig["ScreenTip"]["forword_tip"].get<std::string>().c_str(), ui.videoWidget->fwbfStepLength() / 1000.0, (double)player->position() / player->duration() * 100));
        });
    connect(ui.leftBtn, &TBPushButton::rightClicked, playListDialog.playList, &QMediaPlaylist::previous);
    connect(ui.rightBtn, &TBPushButton::rightClicked, playListDialog.playList, &QMediaPlaylist::next);

    // 全屏
    connect(ui.fullscreenBtn, &QPushButton::clicked, [&] {ui.videoWidget->setFullScreen(true); });

    // 循环状态
    connect(ui.playbackModePushButton, &TBPushButton::leftClicked, [&]
        {
            switch (playListDialog.playList->playbackMode())
            {
            case QMediaPlaylist::PlaybackMode::CurrentItemInLoop:
                playListDialog.playList->setPlaybackMode(QMediaPlaylist::PlaybackMode::Sequential);
                break;
            case QMediaPlaylist::PlaybackMode::Sequential:
                playListDialog.playList->setPlaybackMode(QMediaPlaylist::PlaybackMode::Loop);
                break;
            case QMediaPlaylist::PlaybackMode::Loop:
                playListDialog.playList->setPlaybackMode(QMediaPlaylist::PlaybackMode::Random);
                break;
            case QMediaPlaylist::PlaybackMode::Random:
                playListDialog.playList->setPlaybackMode(QMediaPlaylist::PlaybackMode::CurrentItemInLoop);
                break;
            default:
                playListDialog.playList->setPlaybackMode(QMediaPlaylist::PlaybackMode::Sequential);
                break;
            }

        });
    connect(ui.playbackModePushButton, &TBPushButton::rightClicked, [&]
        {
            switch (playListDialog.playList->playbackMode())
            {
            case QMediaPlaylist::PlaybackMode::CurrentItemInLoop:
                playListDialog.playList->setPlaybackMode(QMediaPlaylist::PlaybackMode::Random);
                break;
            case QMediaPlaylist::PlaybackMode::Sequential:
                playListDialog.playList->setPlaybackMode(QMediaPlaylist::PlaybackMode::CurrentItemInLoop);
                break;
            case QMediaPlaylist::PlaybackMode::Loop:
                playListDialog.playList->setPlaybackMode(QMediaPlaylist::PlaybackMode::Sequential);
                break;
            case QMediaPlaylist::PlaybackMode::Random:
                playListDialog.playList->setPlaybackMode(QMediaPlaylist::PlaybackMode::Loop);
                break;
            default:
                playListDialog.playList->setPlaybackMode(QMediaPlaylist::PlaybackMode::Sequential);
                break;
            }

        });
    connect(playListDialog.playList, &QMediaPlaylist::playbackModeChanged, [&]
        {
            config::GlobalConfig["Player"]["playback_mode"] = playListDialog.playList->playbackMode();
            switch (playListDialog.playList->playbackMode())
            {
            case QMediaPlaylist::PlaybackMode::CurrentItemInLoop:
                ui.playbackModePushButton->setIcon(QIcon(":/MediaPlayerXPre/res/currentiteminloop.png"));
                setScreenTip(config::GlobalConfig["ScreenTip"]["PlaybackMode"]["currentiteminloop"]);
                ui.playbackModePushButton->setToolTip(config::GlobalConfig["ScreenTip"]["PlaybackMode"]["currentiteminloop"]);
                break;
            case QMediaPlaylist::PlaybackMode::Sequential:
                ui.playbackModePushButton->setIcon(QIcon(":/MediaPlayerXPre/res/sequential.png"));
                setScreenTip(config::GlobalConfig["ScreenTip"]["PlaybackMode"]["sequential"]);
                ui.playbackModePushButton->setToolTip(config::GlobalConfig["ScreenTip"]["PlaybackMode"]["sequential"]);
                break;
            case QMediaPlaylist::PlaybackMode::Loop:
                ui.playbackModePushButton->setIcon(QIcon(":/MediaPlayerXPre/res/loop.png"));
                setScreenTip(config::GlobalConfig["ScreenTip"]["PlaybackMode"]["loop"]);
                ui.playbackModePushButton->setToolTip(config::GlobalConfig["ScreenTip"]["PlaybackMode"]["loop"]);
                break;
            case QMediaPlaylist::PlaybackMode::Random:
                ui.playbackModePushButton->setIcon(QIcon(":/MediaPlayerXPre/res/random.png"));
                setScreenTip(config::GlobalConfig["ScreenTip"]["PlaybackMode"]["random"]);
                ui.playbackModePushButton->setToolTip(config::GlobalConfig["ScreenTip"]["PlaybackMode"]["random"]);
                break;
            default:
                playListDialog.playList->setPlaybackMode(QMediaPlaylist::PlaybackMode::Sequential);
                break;
            }
        });
    connect(playListDialog.playList, &QMediaPlaylist::currentIndexChanged, [&](int index)
        {
            setScreenTip(QFileInfo(playListDialog.playList->currentMedia().canonicalUrl().toLocalFile()).fileName());
            setWindowTitle("MediaPlayerXPre - " + QFileInfo(playListDialog.playList->currentMedia().canonicalUrl().toLocalFile()).completeBaseName());
        });

    // 视频设置
    connect(ui.optionButton, &QPushButton::clicked, [&]
        {
            if (optionDialog.isVisible())
                optionDialog.hide();
            else
                optionDialog.show();
            setScreenTip(QString::asprintf("%s: %s",config::GlobalConfig["ScreenTip"]["VideoOption"]["caption"].get<std::string>().c_str()
                , optionDialog.isVisible() 
                ? config::GlobalConfig["ScreenTip"]["show"].get<std::string>().c_str() 
                : config::GlobalConfig["ScreenTip"]["hide"].get<std::string>().c_str()));
        });

    connect(optionDialog.ui.brightnessSlider, &QSlider::valueChanged, [&](int value)
        {
            ui.videoWidget->setBrightness(value);
            setScreenTip(QString::asprintf("%s %+d%%", config::GlobalConfig["ScreenTip"]["VideoOption"]["brightness"].get<std::string>().c_str(), value));
            GlobalConfig["VideoOption"]["brightness"] = value;
        });
    connect(optionDialog.ui.contrastSlider, &QSlider::valueChanged, [&](int value)
        {
            ui.videoWidget->setContrast(value);
            setScreenTip(QString::asprintf("%s %+d%%", config::GlobalConfig["ScreenTip"]["VideoOption"]["contrast"].get<std::string>().c_str(), value));
            GlobalConfig["VideoOption"]["contrast"] = value;
        });
    connect(optionDialog.ui.hueSlider, &QSlider::valueChanged, [&](int value)
        {
            ui.videoWidget->setHue(value);
            setScreenTip(QString::asprintf("%s %+d%%", config::GlobalConfig["ScreenTip"]["VideoOption"]["hue"].get<std::string>().c_str(), value));
            GlobalConfig["VideoOption"]["hue"] = value;
        });
    connect(optionDialog.ui.saturationSlider, &QSlider::valueChanged, [&](int value)
        {
            ui.videoWidget->setSaturation(value);
            setScreenTip(QString::asprintf("%s %+d%%", config::GlobalConfig["ScreenTip"]["VideoOption"]["saturation"].get<std::string>().c_str(), value));
            GlobalConfig["VideoOption"]["saturation"] = value;
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
            setScreenTip(QString::asprintf("%s: %s", config::GlobalConfig["ScreenTip"]["playlist"].get<std::string>().c_str()
                , playListDialog.isVisible()
                ? config::GlobalConfig["ScreenTip"]["show"].get<std::string>().c_str()
                : config::GlobalConfig["ScreenTip"]["hide"].get<std::string>().c_str()));
        });


    // 作者
    connect(ui.btnAbout, &QPushButton::clicked, [&]
        {
            if (authorInformation.isVisible())
                authorInformation.hide();
            else
                authorInformation.show();
        });
}
