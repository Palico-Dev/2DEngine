#include "EngineCore.h"
#include "AssetManager.h"
#include "Asset.h"
#include "FileManager.h"
#

void AssetManager::Load(json::JSON& _json, std::string& _scene)
{
	if (!_json.hasKey("assets"))
	{
		Debug::Warning("No Assets Loaded!");
		return;
	}

	json::JSON metaJSON, jsonMetaArr = _json["assets"];
	std::string metaFileName = "";
	std::vector<STRCODE> metaArr;
	Asset* newAsset;
	STRCODE newUid;

	// assuming [_json].assets is an array of all meta file locations
	for (auto& meta : jsonMetaArr.ArrayRange())
	{
		metaFileName = meta.ToString();
		metaJSON = LoadJson(metaFileName);

		// skip the meta file if it's missing any info
		if (!metaJSON.hasKey("Guid") || !metaJSON.hasKey("Type") || !metaJSON.hasKey("Asset"))
		{
			std::cout << "Meta File '" << metaFileName << "' is incomplete.\n";
			continue;
		}

		newUid = GetHashCode(metaJSON["Guid"].ToString().c_str());
		metaArr.push_back(newUid);

		// if asset already exists, increment refCount instead of creating a duplicate
		if (assets.count(newUid))
		{
			assets[newUid]->refCount++;
		}
		// if not, add a new asset to the map
		else
		{
			newAsset = (Asset*)TypeClass::ConstructObject(metaJSON["Type"].ToString().c_str());
			newAsset->SetId(newUid);
			//newAsset->type = metaJSON["Type"].ToString();
			//newAsset->path = metaJSON["Asset"].ToString();
			//newAsset->refCount++;
			//newAsset->Load();

			assets.emplace(newUid, newAsset);
		}
	}

	// store meta STRCODEs to assetMeta map for later destruction
	assetMeta.emplace(_scene, metaArr);
}

void AssetManager::Unload(std::string& _scene)
{
	try
	{
		if (!assetMeta.count(_scene))
		{
			std::cout << "No asset detected for scene: " + _scene + ". Asset unload process is skipped.\n";
			return;
		}

		for (auto& _strcode : assetMeta.at(_scene))
		{
			Asset* asset_to_unload = assets.at(_strcode);
			int& count = asset_to_unload->refCount;

			if (!count) std::cout << "WARNING! Attempting to unload an asset with no instance.\n";
			else count--;

			if (!count)
			{
				asset_to_unload->Destroy();
				delete asset_to_unload;
				assets.erase(_strcode);
			}
		}
		assetMeta.at(_scene).clear();
		assetMeta.erase(_scene);
	}
	catch (const std::out_of_range& e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
	}
}

Asset* AssetManager::GetAsset(const char* _guid)
{
	return assets.at(GetHashCode(_guid));
}

void AssetManager::Initialize()
{
	GenerateMetaDB();
}

void AssetManager::Destroy()
{
	for (auto& asset : assets)
	{
		asset.second->Destroy();
		delete asset.second;
		assets.erase(asset.first);
	}
}

void AssetManager::GenerateMetaDB()
{
	auto filePath = FileManager::GetALLMetaFiles(FileManager::GetAssetPath());
	for (auto& p : filePath)
	{
		auto j = FileManager::LoadJson(p.c_str());
		std::string guid = FileManager::JsonReadString(j, "Guid");
		metaDatabase.emplace(GetHashCode(guid.c_str()), p);
	}
}

void AssetManager::LoadEngineAsset()
{
	auto filePath = FileManager::GetALLMetaFiles(FileManager::GetEngineAssetPath());
	for (auto& p : filePath)
	{
		auto j = FileManager::LoadJson(p.c_str());
		std::string type = FileManager::JsonReadString(j, "Type");
		std::string fileName = FileManager::JsonReadString(j, "FileName");

		Asset* asset = (Asset*)CreateObject(type.c_str());
		engineAssets.emplace(fileName, asset);
	}
}
