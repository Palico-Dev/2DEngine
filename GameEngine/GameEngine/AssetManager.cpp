#include "EngineCore.h"
#include "AssetManager.h"
#include "Asset.h"
#include "FileManager.h"

void AssetManager::Load(json::JSON& _json)
{
	if (!_json.hasKey("assets"))
	{
		Debug::Warning("No Assets Loaded!");
		return;
	}

	json::JSON metaArray = _json["assets"];

	for (auto& meta : metaArray.ArrayRange())
	{
		std::string fileName = meta.ToString();
		std::string path = metaDatabase[GetHashCode(fileName.c_str())];

		if (assets.count(GetHashCode(fileName.c_str())))
		{
			assets[GetHashCode(fileName.c_str())]->refCount++;
		}
		else
		{
			json::JSON j = FileManager::LoadJson(path.c_str());
			Asset* newAsset = (Asset*)CreateObject(FileManager::JsonReadString(j, "Type").c_str());
			newAsset->Load(j);

			assets.emplace(GetHashCode(fileName.c_str()), newAsset);
		}
	}
}

void AssetManager::Unload(std::string& _scene)
{
	//try
	//{
	//	if (!assetMeta.count(_scene))
	//	{
	//		std::cout << "No asset detected for scene: " + _scene + ". Asset unload process is skipped.\n";
	//		return;
	//	}

	//	for (auto& _strcode : assetMeta.at(_scene))
	//	{
	//		Asset* asset_to_unload = assets.at(_strcode);
	//		int& count = asset_to_unload->refCount;

	//		if (!count) std::cout << "WARNING! Attempting to unload an asset with no instance.\n";
	//		else count--;

	//		if (!count)
	//		{
	//			asset_to_unload->Destroy();
	//			delete asset_to_unload;
	//			assets.erase(_strcode);
	//		}
	//	}
	//	assetMeta.at(_scene).clear();
	//	assetMeta.erase(_scene);
	//}
	//catch (const std::out_of_range& e)
	//{
	//	std::cerr << "Error: " << e.what() << std::endl;
	//}
}

Asset* AssetManager::GetAsset(const char* fileName)
{
	return assets.at(GetHashCode(fileName));
}

Asset* AssetManager::GetEngineAsset(const char* fileName)
{
	return engineAssets.at(fileName);
}

std::string& AssetManager::GetAssetPath(const char* fileName)
{
	return metaDatabase.at(GetHashCode(fileName));
}

void AssetManager::Initialize()
{
	GenerateMetaDB();
	LoadEngineAsset();
}

void AssetManager::Destroy()
{
	for (auto& asset : assets)
	{
		asset.second->Destroy();
		delete asset.second;
	}
	for (auto& asset : engineAssets)
	{
		asset.second->Destroy();
		delete asset.second;
	}
	assets.clear();
	engineAssets.clear();
}

void AssetManager::GenerateMetaDB()
{
	auto filePath = FileManager::GetALLMetaFiles(FileManager::GetAssetFolderPath());
	for (auto& p : filePath)
	{
		auto j = FileManager::LoadJson(p.c_str());
		std::string guid = FileManager::JsonReadString(j, "Guid");
		std::string fileName = FileManager::JsonReadString(j, "FileName");
		metaDatabase.emplace(GetHashCode(fileName.c_str()), p);
	}
}

void AssetManager::LoadEngineAsset()
{
	auto filePath = FileManager::GetALLMetaFiles(FileManager::GetEngineAssetFolderPath());
	for (auto& p : filePath)
	{
		auto j = FileManager::LoadJson(p.c_str());
		std::string type = FileManager::JsonReadString(j, "Type");
		std::string fileName = FileManager::JsonReadString(j, "FileName");

		metaDatabase.emplace(GetHashCode(fileName.c_str()), p);
		
		if (type == "Scene")
			continue;

		Asset* asset = (Asset*)CreateObject(type.c_str());
		asset->Load(j);
		engineAssets.emplace(fileName, asset);

	}
}
