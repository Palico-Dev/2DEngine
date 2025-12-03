#include "EngineCore.h"
#include "Engine.h"
#include "InputManager.h"
#include "RenderSystem.h"
#include "CollisionSystem.h"
#include "AssetManager.h"
#include "SceneManager.h"
#include "FileManager.h"

extern void Engine_Register();

void Engine::Initialize()
{
    Engine_Register();

	LoadGameSettings();

	RenderSystem::Instance().Initialize();
	AssetManager::Instance().Initialize();
	Time::Instance().Initialize();

    SceneManager::Instance().Initialize();
    InputManager::Instance().Initialize();
    CollisionSystem::Instance().Initialize();


}

void Engine::Destroy()
{
    RenderSystem::Instance().Destroy();
    CollisionSystem::Instance().Destroy();
    SceneManager::Instance().Destroy();
    AssetManager::Instance().Destroy();
}

void Engine::GameLoop()
{
    SceneManager::Instance().Start();

	while (!quit)
	{
        // PreUpdate TBD

		Time::Instance().Update();
        InputManager::Instance().Update();
        SceneManager::Instance().Update();
        CollisionSystem::Instance().Update();
        RenderSystem::Instance().Update();

        // PostUpdate TBD
	}
}

void Engine::LoadGameSettings()
{
	gameSettings = FileManager::LoadJson(FileManager::GetGameSettingPath().string().c_str());

	//if (gameSettings.hasKey("Scenes")) {
	//	json::JSON scenesJson = root.at("Scenes");
	//	SceneManager& sceneManager = SceneManager::Instance();
	//	for (auto& sceneEntry : scenesJson.ArrayRange()) {
	//		sceneManager.RegisterScene(
	//			sceneEntry.at("SceneName").ToString(),
	//			sceneEntry.at("FilePath").ToString()
	//		);
	//	}
	//}
	//std::string startupScene = FileManager::JsonReadString(gameSettings, "StartupScene");
	//SceneManager::Instance().LoadScene(AssetManager::Instance().GetAssetPath(startupScene.c_str()).c_str());
}
