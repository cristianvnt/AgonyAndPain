#include "ConfigParser.h"

ConfigParser::ConfigParser(const std::string_view& file) : _currentSection{ "GLOBAL" }
{
	Load(file);
}

void ConfigParser::Load(const std::string_view& file)
{
	std::cout << "HMMMMM DEBUG: Loading config from: " << file << "\n";

	std::ifstream data{ std::string(file) };

	if (!data.is_open())
	{
		std::cerr << "NOOOOO ERROR: couldnt open file\n";
		return;
	}

	std::string content;
	while (std::getline(data, content))
	{
		if (content.empty())
			continue;

		std::string_view parseData{ content };
		if (parseData.front() == '[' && parseData.back() == ']')
		{
			_currentSection = parseData.substr(1, parseData.size() - 2);
			continue;
		}

		std::size_t eq = parseData.find('=');
		if (eq != std::string::npos)
		{
			std::string_view key = parseData.substr(0, eq);
			std::string_view value = parseData.substr(eq + 1);

			std::size_t foundFirst = key.find_first_not_of(" \t\f\v\n\r");
			std::size_t foundLast = key.find_last_not_of(" \t\f\v\n\r");
			if (foundFirst != std::string::npos)
				key = key.substr(foundFirst, foundLast - foundFirst + 1);

			foundFirst = value.find_first_not_of(" \t\f\v\n\r");
			foundLast = value.find_last_not_of(" \t\f\v\n\r");
			if (foundFirst != std::string::npos)
				value = value.substr(foundFirst, foundLast - foundFirst + 1);

			_configData[_currentSection].emplace(key, value);
		}
	}
}

std::string ConfigParser::GetString(const std::string_view& section, const std::string_view& key)
{
	if (auto it = _configData.find(std::string(section)); it != _configData.end())
		if (auto innerIt = it->second.find(std::string(key)); innerIt != it->second.end())
			return innerIt->second;

	return "";
}