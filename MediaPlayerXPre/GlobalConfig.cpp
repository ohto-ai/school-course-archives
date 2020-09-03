#include "GlobalConfig.h"

namespace config
{
	nlohmann::json GlobalConfig;
	void loadConfig()
	{
		std::ifstream in(ConfigFilePath);
		if (!in)
			saveConfig();
		std::istreambuf_iterator<char> begin(in);
		std::istreambuf_iterator<char> end;
		GlobalConfig = nlohmann::json::parse(std::string(begin, end));
	}
	void saveConfig()
	{
		std::ofstream out(ConfigFilePath);
		out << GlobalConfig.dump();
	}
}