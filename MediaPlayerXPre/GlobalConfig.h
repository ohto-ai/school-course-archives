#pragma once
#include <json.hpp>
#include <fstream>


namespace config
{
	extern nlohmann::json GlobalConfig;
	constexpr auto ConfigFilePath = "./application-config.json";
	void loadConfig();
	void saveConfig();
}


