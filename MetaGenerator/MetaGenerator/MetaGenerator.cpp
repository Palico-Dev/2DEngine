#include "EngineCore.h"
#include <iostream>
#include <filesystem>
#undef main

namespace fs = std::filesystem;
enum class AssetLocation { Engine, Project };

std::string GetAssetType(fs::path assetPath)
{
	static const std::unordered_map<std::string, std::string> extensionToType = {
		{".png", "TextureAsset"},
		{".jpg", "TextureAsset"},
		{".wav", "SoundAsset"},
		{".ttf","FontAsset"},
		{".prefab","PrefabAsset"},
		{".scene","Scene"},
	};

	auto it = extensionToType.find(assetPath.extension().string());
	if (it != extensionToType.end())
		return it->second;

	return "Unknown";
}


void CreateMetaFile_(fs::path assetPath,fs::path folderPath,AssetLocation location)
{
	fs::path metaPath = assetPath;
	metaPath += ".meta";

	json::JSON j;



	j["Type"] = GetAssetType(assetPath);

	if (location == AssetLocation::Engine)
	{
		j["Location"] = "Engine";
		j["FileName"] = assetPath.stem().string();
	}
	else
	{
		j["Location"] = "Project";
		j["FileName"] = assetPath.filename().string();
	}

	UUID _uid;
	CreateUUID(&_uid);

	j["Guid"] = GUIDTostring(_uid);

	fs::path relativePath = fs::relative(assetPath, folderPath);

	std::string pathStr = relativePath.string();
	std::replace(pathStr.begin(), pathStr.end(), '\\', '/'); 


	j["Asset"] = pathStr;

	std::ofstream metaFile(metaPath);
	if (!metaFile)
	{
		std::cerr << "Failed to create: " << metaPath << "\n";
		return;
	}

	metaFile << j.dump()<<std::endl;

	std::cout << "Generated: " << metaPath << "\n";
}

void Generate(fs::path path,AssetLocation loc)
{

	fs::path assetsDir = path;

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
			else if(filePath.extension() != ".json")
			{
				fs::path metaPath = filePath;
				metaPath += ".meta";

				if (fs::exists(metaPath))
				{
					continue;
				}

				CreateMetaFile_(filePath,path, loc);
			}



		}
	}
}

void Clean(fs::path path)
{
	fs::path assetsDir = path;

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
	//Clean(ASSET_DIR);
	//Clean(ENGINEASSET_DIR);
	Generate(ASSET_DIR,AssetLocation::Project);
	Generate(ENGINEASSET_DIR,AssetLocation::Engine);

}

