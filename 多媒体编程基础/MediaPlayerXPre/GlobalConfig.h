#pragma once
#include <json.hpp>
#include <fstream>
#include <QString>
#include <QMediaPlaylist>


namespace config
{
	extern nlohmann::json GlobalConfig;
	constexpr auto ConfigFilePath = "./application-config.json";
	bool loadConfig();
	void resetConfig();
	void saveConfig();

}
void from_json(const nlohmann::json& j, QString& s);
void from_json(const nlohmann::json& j, QMediaPlaylist::PlaybackMode& m);
void to_json(nlohmann::json& j, const QString& s);
void to_json(nlohmann::json& j, const QMediaPlaylist::PlaybackMode& m);


