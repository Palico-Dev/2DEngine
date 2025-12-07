#include "EngineCore.h"
#include "FileManager.h"

#ifdef _WIN32
#include <windows.h>
#endif

json::JSON FileManager::LoadJson(const char* path)
{
	std::ifstream file(path);
	if (!file.is_open())
	{
		Debug::Error(std::string("CANNOT load json file:") + path);
	}

	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string content = buffer.str();
	json::JSON j = json::JSON::Load(content);
	return j;
}

int FileManager::JsonReadInt(json::JSON& j, const char* key)
{
	if (j.hasKey(key))
	{
		return j[key].ToInt();
	}

	Debug::Warning(std::string("CANNOT read key: ") + key);
	return -1;
}

float FileManager::JsonReadFloat(json::JSON& j, const char* key)
{
	if (j.hasKey(key))
	{
		return j[key].ToFloat();
	}

	Debug::Warning(std::string("CANNOT read key: ") + key);
	return -1.0f;
}

std::string FileManager::JsonReadString(json::JSON& j, const char* key)
{
	if (j.hasKey(key))
	{
		return j[key].ToString();
	}

	Debug::Warning(std::string("CANNOT read key: ") + key);
	return "";
}

glm::vec2 FileManager::JsonReadVec2(json::JSON& j, const char* key)
{
	if (j.hasKey(key))
	{
		json::JSON& vecObj = j[key];

		float x = JsonReadFloat(vecObj, "x");
		float y = JsonReadFloat(vecObj, "y");

		return glm::vec2(x, y);
	}

	Debug::Warning(std::string("CANNOT read Vec2 key: ") + key);
	return glm::vec2(0.0f);
}

json::JSON FileManager::JsonReadJson(json::JSON& j, const char* key)
{
	if (j.hasKey(key))
	{
		return j[key];
	}
	Debug::Warning(std::string("CANNOT read key: ") + key);
	return json::JSON();
}

bool FileManager::JsonReadBool(json::JSON& j, const char* key)
{
	if (j.hasKey(key))
	{
		return j[key].ToBool();
	}
	Debug::Warning(std::string("CANNOT read key: ") + key);
	return false;
}

glm::vec4 FileManager::JsonReadColor(json::JSON& j, const char* key)
{
	if (j.hasKey(key))
	{
		json::JSON& c = j[key];

		float r = std::clamp(JsonReadFloat(c, "r"), 0.0f, 1.0f);
		float g = std::clamp(JsonReadFloat(c, "g"), 0.0f, 1.0f);
		float b = std::clamp(JsonReadFloat(c, "b"), 0.0f, 1.0f);
		float a = std::clamp(JsonReadFloat(c, "a"), 0.0f, 1.0f);

		return glm::vec4(r, g, b, a);
	}

	Debug::Warning(std::string("CANNOT read Color: ") + key);
	return glm::vec4(0.0f);
}

std::vector<json::JSON> FileManager::JsonReadArray(json::JSON j, const std::string& key)
{
	std::vector<json::JSON> result;

	if (!j.hasKey(key) || j[key].JSONType()!=json::JSON::Class::Array)
	{
		Debug::Warning(std::string("CANNOT read Array: ") + key);
		return result;
	}

	for (auto& node : j[key].ArrayRange())
	{
		result.push_back(node);
	}

	return result;
}

std::vector<std::string> FileManager::GetALLMetaFiles(fs::path path)
{
	std::vector<std::string> res;
	fs::path assetsDir = path;

	if (!fs::exists(assetsDir))
	{
		Debug::Error("Assets folder not find!");
		return res;
	}
	for (const auto& entry : fs::recursive_directory_iterator(assetsDir))
	{
		if (entry.is_regular_file())
		{
			fs::path filePath = entry.path();

			if (filePath.extension() == ".meta")
			{
				res.push_back(filePath.string());
			}
		}
	}
	return res;
}

fs::path FileManager::GetExecutableDir()
{
#ifdef _WIN32
	char buffer[MAX_PATH];
	GetModuleFileNameA(NULL, buffer, MAX_PATH);
	return fs::path(buffer).parent_path();
#else
	return fs::current_path();
#endif
}

fs::path FileManager::GetAssetFolderPath()
{
#ifdef _DEBUG
	return fs::path(ASSET_DIR);
#else
	return GetExecutableDir() / "ProjectAssets";
#endif
}

fs::path FileManager::GetEngineAssetFolderPath()
{
#ifdef _DEBUG 
	return fs::path(ENGINEASSET_DIR);
#else
	return GetExecutableDir() / "EngineAssets";
#endif
}

fs::path FileManager::GetGameSettingPath()
{
	return GetAssetFolderPath() / "Config" / "GameSettings.json";
}

fs::path FileManager::GetAssetPath(json::JSON j)
{
	fs::path path;
	if (FileManager::JsonReadString(j, "Location") == "Engine")
	{
		path = GetEngineAssetFolderPath();
	}
	else
	{
		path = FileManager::GetAssetFolderPath();
	}
	path = path / FileManager::JsonReadString(j, "Asset");

	return path;
}
