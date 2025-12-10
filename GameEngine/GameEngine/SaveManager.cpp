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

	if (gameCallback != nullptr)
		gameCallback(save);

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
}

void SaveManager::Deserialize(json::JSON& j)
{

}
