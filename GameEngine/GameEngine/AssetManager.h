#pragma once

#ifndef _ASSETMANAGER_H_
#define _ASSETMANAGER_H_

class Asset;

class AssetManager final
{
	DECLARE_SINGLETON(AssetManager)

public:
	void Load(json::JSON& _json);
	void Unload(std::string& _scene);
	Asset* GetAsset(const std::string& fileName);
	Asset* GetEngineAsset(const std::string& fileName);


	std::string& GetAssetPath(const std::string& fileName);


private:
	void Initialize();
	void Destroy();

	void GenerateMetaDB();
	void LoadEngineAsset();

private:
	std::map<STRCODE, Asset*> assets;
	std::map<STRCODE, std::string> metaDatabase;

	std::map<std::string, Asset*> engineAssets;
	friend class Engine;



};

#endif
