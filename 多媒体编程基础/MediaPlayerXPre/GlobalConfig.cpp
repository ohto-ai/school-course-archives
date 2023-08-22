#include "GlobalConfig.h"
#include <exception>
#pragma execution_character_set("utf-8")

namespace config
{
	nlohmann::json GlobalConfig;
	bool loadConfig()
	{
		std::ifstream in(ConfigFilePath);
        if (!in)
            return false;
		std::istreambuf_iterator<char> begin(in);
		std::istreambuf_iterator<char> end;
		std::string cont(begin, end);
        if (cont.empty())
            return false;
		GlobalConfig = nlohmann::json::parse(cont);
        return true;
	}
	void resetConfig()
    {
        auto& configMainWindow = config::GlobalConfig["MainWindow"];
        configMainWindow["x"] = 200;
        configMainWindow["y"] = 100;
        configMainWindow["width"] = 950;
        configMainWindow["height"] = 600;

        auto& configScreenTip = config::GlobalConfig["ScreenTip"];
        configScreenTip["tip_delay"] = 1500;
        configScreenTip["forword_tip"] = "快进 %.3f(%.0lf%%)";
        configScreenTip["backword_tip"] = "快退 %.3f(%.0lf%%)";
        configScreenTip["medias_loaded"] = "%d个媒体文件已载入";

        auto& configPlayer = config::GlobalConfig["Player"];
        configPlayer["ImportDirectory"]["caption"] = "选择文件夹";
        configPlayer["ImportDirectory"]["name_filters"] =
            nlohmann::json::array({ "*.mp3", "*.wav", "*.wma", "*.ogg", "*.acc", "*.flac", "*.3gp"
                , "*.wmv", "*.avi", "*.mp4", "*.mpeg", "*.mkv", "*.rmvb", "*.flv" });
        configPlayer["ImportFiles"]["caption"] = "选择媒体文件";
        configPlayer["ImportFiles"]["filter"] = "支持的媒体文件(*.mp3;*.wav;*.wma;*.ogg;*.acc;*.flac;*.wmv;*.avi;*.mp4;*.mpeg;*.mkv;*.rmvb;*.flv;*.3gp);;\
视频(*.wmv;*.avi;*.mp4;*.mpeg;*.mkv;*.rmvb;*.flv;*.3gp);;\
音频(*.mp3;*.wav;*.wma;*.ogg;*.acc;*.flac);;\
全部(*.*)";


        configPlayer["volume"] = 50;

        configPlayer["playback_mode"] = QMediaPlaylist::PlaybackMode::Sequential;

        configScreenTip["PlaybackMode"]["currentiteminloop"] = "单曲循环";
        configScreenTip["PlaybackMode"]["sequential"] = "顺序播放";
        configScreenTip["PlaybackMode"]["loop"] = "列表循环";
        configScreenTip["PlaybackMode"]["random"] = "随机播放";
        configScreenTip["capture"] = "图像已存入剪切板";

        configScreenTip["show"] = "显示";
        configScreenTip["hide"] = "隐藏";

        configScreenTip["VideoOption"]["caption"] = "视频设置";
        configScreenTip["VideoOption"]["brightness"] = "亮度";
        configScreenTip["VideoOption"]["contrast"] = "对比度";
        configScreenTip["VideoOption"]["hue"] = "色相";
        configScreenTip["VideoOption"]["saturation"] = "饱和度";
        configScreenTip["playlist"] = "播放列表";
        configScreenTip["play"] = "播放";
        configScreenTip["pause"] = "暂停";
        configScreenTip["stop"] = "停止";
        configScreenTip["position"] = "进度";
        configScreenTip["muted"] = "静音";
        configScreenTip["volume"] = "音量";

        auto& configPlaylistDialog = config::GlobalConfig["PlaylistDialog"];
        configPlaylistDialog["x"] = 750;
        configPlaylistDialog["y"] = 200;
        configPlaylistDialog["width"] = 480;
        configPlaylistDialog["height"] = 400;
        configPlaylistDialog["caption"] = "播放列表";
        configPlaylistDialog["CustomContextMenu"]["play"] = "播放此项";
        configPlaylistDialog["CustomContextMenu"]["locate"] = "打开目录";
        configPlaylistDialog["CustomContextMenu"]["remove"] = "移除此项";
        configPlaylistDialog["CustomContextMenu"]["clear"] = "清空列表";


        auto& configOptionDialog = config::GlobalConfig["OptionDialog"];
        configOptionDialog["x"] = 750;
        configOptionDialog["y"] = 400;
        configOptionDialog["width"] = 400;
        configOptionDialog["height"] = 160;
        configOptionDialog["caption"] = "视频设置";


        config::GlobalConfig["VideoOption"]["brightness"] = 0;
        config::GlobalConfig["VideoOption"]["contrast"] = 0;
        config::GlobalConfig["VideoOption"]["hue"] = 0;
        config::GlobalConfig["VideoOption"]["saturation"] = 0;

        config::saveConfig();
    }
	void saveConfig()
	{
		std::ofstream out(ConfigFilePath);
		out << GlobalConfig.dump(4);
	}
}