#include "EngineCore.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "Engine.h"
#include "FileManager.h"
#include "UISystem.h"
#include "Entity.h"

void SceneManager::Initialize()
{
	json::JSON gameSettings = Engine::Instance().GetGameSettings();

	std::string startupScene = FileManager::JsonReadString(gameSettings, "StartupScene");

	LoadScene(AssetManager::Instance().GetAssetPath(startupScene.c_str()).c_str());

}

void SceneManager::Update()
{
	for (auto& s : scenes)
	{
		s->Update();
	}
}

void SceneManager::Destroy()
{

	for (auto& s : scenes)
	{
		s->Destroy();
		delete s;
	}

}

void SceneManager::Start()
{

}



void SceneManager::LateUpdate()
{

}

void SceneManager::LoadScene(const char* path)
{
	Debug::Log(std::string("Load Scene :") + path);

	json::JSON sceneMetaJson = FileManager::LoadJson(path);

	fs::path scenePath = FileManager::GetAssetPath(sceneMetaJson);

	json::JSON sceneJson = FileManager::LoadJson(scenePath.generic_string().c_str());
	AssetManager::Instance().Load(sceneJson);

	if (sceneJson.hasKey("scene"))
	{
		json::JSON j = sceneJson["scene"];
		Scene* scene = (Scene*)CreateObject("Scene");
		scene->Load(j);
		scene->Initialize();

		scenes.push_back(scene);
		currentScene = scene;
	}

	UISystem::Instance().Load(sceneJson);
}
