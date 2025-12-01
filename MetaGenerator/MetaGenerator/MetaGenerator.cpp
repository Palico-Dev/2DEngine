#include "EngineCore.h"
#include <iostream>
#include <filesystem>
#undef main

namespace fs = std::filesystem;

std::string GetAssetType(fs::path assetPath)
{
	static const std::unordered_map<std::string, std::string> extensionToType = {
		{".png", "TextureAsset"},
		{".jpg", "TextureAsset"},
		{".json", "Json"},
		{".wav", "SoundAsset"},
		{".ttf","FontAsset"},
		{".prefab","PrefabAsset"},
	};

	auto it = extensionToType.find(assetPath.extension().string());
	if (it != extensionToType.end())
		return it->second;

	return "Unknown";
}


void CreateMetaFile_(fs::path assetPath)
{
	fs::path metaPath = assetPath;
	metaPath += ".meta";

	json::JSON j;

	j["Type"] = GetAssetType(assetPath);

	UUID _uid;
	CreateUUID(&_uid);

	j["Guid"] = GUIDTostring(_uid);

	fs::path relativePath = fs::relative(assetPath, ASSET_DIR);

	std::string pathStr = relativePath.string();
	std::replace(pathStr.begin(), pathStr.end(), '\\', '/'); 

	std::string finalPath = "../Assets/" + pathStr;


	j["Asset"] = finalPath;

	std::ofstream metaFile(metaPath);
	if (!metaFile)
	{
		std::cerr << "Failed to create: " << metaPath << "\n";
		return;
	}

	metaFile << j.dump()<<std::endl;

	std::cout << "Generated: " << metaPath << "\n";
}

void Generate()
{

	fs::path assetsDir = ASSET_DIR;

	if (!fs::exists(assetsDir))
	{
		std::cerr << "Assets folder not found!\n";
		return ;
	}
	for (const auto& entry : fs::recursive_directory_iterator(assetsDir))
	{
		if (entry.is_regular_file())
		{
			fs::path filePath = entry.path();

			if (filePath.extension() == ".meta")
			{
				if (!fs::exists(filePath.replace_extension("")))
				{
					std::error_code ec;
					fs::remove(entry.path(), ec);
					if (!ec)
					{
						std::cout << "Deleted: " << entry.path() << "\n";
					}
				}
			}
			else
			{
				fs::path metaPath = filePath;
				metaPath += ".meta";

				if (fs::exists(metaPath))
				{
					continue;
				}

				CreateMetaFile_(filePath);
			}



		}
	}
}

void Clean()
{
	fs::path assetsDir = ASSET_DIR;

	if (!fs::exists(assetsDir))
	{
		std::cerr << "Assets folder not found!\n";
		return;
	}
	for (const auto& entry : fs::recursive_directory_iterator(assetsDir))
	{
		if (entry.is_regular_file() && entry.path().extension() == ".meta")
		{
			std::error_code ec;
			fs::remove(entry.path(), ec);
			if (!ec)
			{
				std::cout << "Deleted: " << entry.path() << "\n";
			}
		}
	}
}

int main()
{
	//Clean();
	Generate();

}

