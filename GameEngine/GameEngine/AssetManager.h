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
	
	template <typename T>
	T* GetAsset(const std::string& fileName)
	{
		Asset* rawAsset = GetAssetInternal(fileName);
		if (!rawAsset) return nullptr;
		return (T*)(rawAsset);
	}

	template <typename T>
	T* GetEngineAsset(const std::string& fileName)
	{
		Asset* rawAsset = GetEngineAssetInternal(fileName);
		if (!rawAsset) return nullptr;
		return static_cast<T*>(rawAsset);
	}



	std::string& GetAssetPath(const std::string& fileName);


private:
	void Initialize();
	void Destroy();

	void GenerateMetaDB();
	void LoadEngineAsset();

	Asset* GetAssetInternal(const std::string& fileName);
	Asset* GetEngineAssetInternal(const std::string& fileName);

private:
	std::map<STRCODE, Asset*> assets;
	std::map<STRCODE, std::string> metaDatabase;

	std::map<std::string, Asset*> engineAssets;
	friend class Engine;



};

#endif
