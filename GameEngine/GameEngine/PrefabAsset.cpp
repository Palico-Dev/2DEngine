#include "EngineCore.h"
#include "PrefabAsset.h"
#include "Entity.h"
#include "FileManager.h"

IMPLEMENT_DYNAMIC_CLASS(PrefabAsset)

void PrefabAsset::Load(json::JSON j, std::string& _fileName)
{
    fileName = _fileName;
    fs::path path = FileManager::GetAssetPath(j);

    json::JSON prefabJson = FileManager::LoadJson(path.generic_string().c_str());
    prefab = (Entity*)CreateObject("Entity");
    prefab->Load(prefabJson);

}

void PrefabAsset::Destroy()
{
    prefab->Destroy();
    prefab = nullptr;
}
