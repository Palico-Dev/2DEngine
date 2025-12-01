#pragma once

#ifndef _ASSETMANAGER_H_
#define _ASSETMANAGER_H_

class Asset;

class AssetManager final
{
	DECLARE_SINGLETON(AssetManager)

private:
	std::map<STRCODE, Asset*> assets;
	std::map<std::string, std::vector<STRCODE>> assetMeta;
	friend class Engine;

	void Initialize();
	void Destroy();
public:
	void Load(json::JSON& _json, std::string& _scene);
	void Unload(std::string& _scene);
	template<typename T> T* GetAsset(const char* _guid)
	{
		try {
			// get loaded asset from map and cast pointer type to T*
			return (T*)assets.at(GetHashCode(_guid));
		}
		catch (const std::out_of_range& e)
		{
			std::cerr << "Error: " << e.what() << std::endl;
		}
	}
};

#endif
