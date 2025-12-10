#include "EngineCore.h"
#include "SaveManager.h"
#include "Scene.h"
#include "SceneManager.h"
#include "Entity.h"
#include "FileManager.h"

void SaveManager::SaveGame()
{
	Debug::Log("Save Game");

	json::JSON save;

	Serialize(save);

	std::filesystem::path folderPath = FileManager::GetSavePath();
	std::filesystem::path path = folderPath / "save01.save";
	std::ofstream saveFile(path);
	if (!saveFile)
	{
		Debug::Error("Failed to create : " + FileManager::GetSavePath().generic_string());
		return;
	}

	saveFile << save.dump() << std::endl;

}

void SaveManager::LoadGame()
{
	Debug::Log("Load Game");

	std::filesystem::path folderPath = FileManager::GetSavePath();
	std::filesystem::path path = folderPath / "save01.save";

	json::JSON save = FileManager::LoadJson(path.generic_string());

	Deserialize(save);

}

void SaveManager::Serialize(json::JSON& j)
{
	json::JSON entityNodes = json::JSON::Array();

	for (auto& e : SceneManager::Instance().GetCurrentScene()->entities)
	{
		if (!e->HasTag("DontDestroyOnLoad"))
			entityNodes.append(e->Serialize());
	}
	j["entities"] = entityNodes;

	if (gameSerializeCallback != nullptr)
		gameSerializeCallback(j);
}

void SaveManager::Deserialize(json::JSON& j)
{
	auto entitiesJson = FileManager::JsonReadArray(j, "entities");
	for (auto& eJson : entitiesJson)
	{
		Entity* e = (Entity*)CreateObject("Entity");
		e->Deserialize(eJson);
		Gameplay::Spawn(e);
	}

	if (gameDeserializeCallback != nullptr)
	{
		gameDeserializeCallback(j);
	}
}
