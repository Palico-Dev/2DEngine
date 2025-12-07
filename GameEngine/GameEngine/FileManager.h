#pragma once
#ifndef _FILELOADER_H_
#define _FILELOADER_H_
#include <filesystem>

namespace fs = std::filesystem;

class FileManager
{
public:
	static json::JSON LoadJson(const char* path);
	static int JsonReadInt(json::JSON& j, const char* key);
	static float JsonReadFloat(json::JSON& j, const char* key);
	static std::string JsonReadString(json::JSON& j, const char* key);
	static glm::vec2 JsonReadVec2(json::JSON& j, const char* key);
	static json::JSON JsonReadJson(json::JSON& j, const char* key);
	static bool JsonReadBool(json::JSON& j, const char* key);
	static glm::vec4 JsonReadColor(json::JSON& j, const char* key);
	static std::vector<json::JSON> JsonReadArray(json::JSON j, const std::string& key);

	static std::vector<std::string> GetALLMetaFiles(fs::path path);

	static fs::path GetExecutableDir();
	static fs::path GetAssetFolderPath();
	static fs::path GetEngineAssetFolderPath();
	static fs::path GetGameSettingPath();
	static fs::path GetAssetPath(json::JSON j);

};

#endif

