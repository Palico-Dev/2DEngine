#pragma once
#ifndef _FILELOADER_H_
#define _FILELOADER_H_
#include <filesystem>

namespace fs = std::filesystem;

class FileManager
{
public:
	static json::JSON LoadJson(const std::string& path);
	static int JsonReadInt(json::JSON& j, const std::string& key);
	static float JsonReadFloat(json::JSON& j, const std::string& key);
	static std::string JsonReadString(json::JSON& j, const std::string& key);
	static glm::vec2 JsonReadVec2(json::JSON& j, const std::string& key);
	static json::JSON JsonReadJson(json::JSON& j, const std::string& key);
	static bool JsonReadBool(json::JSON& j, const std::string& key);
	static glm::vec4 JsonReadColor(json::JSON& j, const std::string& key);
	static std::vector<json::JSON> JsonReadArray(json::JSON& j, const std::string& key);

	static void JsonWriteVec2(json::JSON& j, const std::string& key, glm::vec2 vec);
	static void JsonWriteColor(json::JSON& j, const std::string& key, glm::vec4 color);
	static void JsonWriteInt(json::JSON& j, const std::string& key, int value);
	static void JsonWriteFloat(json::JSON& j, const std::string& key, float value);
	static void JsonWriteString(json::JSON& j, const std::string& key, std::string& value);
	static void JsonWriteBool(json::JSON& j, const std::string& key, bool value);
	template <typename T>
	static void JsonWriteArray(json::JSON& j, const std::string& key, const std::vector<T>& list)
	{
		json::JSON arrayNode = json::JSON::Array();
		for (const auto& item : list)
		{
			if constexpr (std::is_same_v<T, unsigned int> || std::is_same_v<T, uint32_t>)
			{
				arrayNode.append((long long)item);
			}
			else
			{
				arrayNode.append(item);
			}	
		}
		j[key] = arrayNode;
	}

	static std::vector<std::string> GetALLMetaFiles(fs::path path);

	static fs::path GetExecutableDir();
	static fs::path GetAssetFolderPath();
	static fs::path GetEngineAssetFolderPath();
	static fs::path GetGameSettingPath();
	static fs::path GetAssetPath(json::JSON j);
	static fs::path GetSavePath();

};

#endif

