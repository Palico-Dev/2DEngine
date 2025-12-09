#include "EngineCore.h"
#include "Engine.h"
#include "InputManager.h"
#include "RenderSystem.h"
#include "CollisionSystem.h"
#include "AssetManager.h"
#include "SceneManager.h"
#include "FileManager.h"
#include "UISystem.h"
#include "Scene.h"

extern void Engine_Register();

void Engine::Initialize()
{
    Engine_Register();

	LoadGameSettings();

	RenderSystem::Instance().Initialize();
	AssetManager::Instance().Initialize();
	Time::Instance().Initialize();

	if (gameInitCallback)
	{
		gameInitCallback();
	}

    SceneManager::Instance().Initialize();
    InputManager::Instance().Initialize();
    CollisionSystem::Instance().Initialize();



	UISystem::Instance().Initialize();
	


}

void Engine::Destroy()
{
	UISystem::Instance().Destroy();
    RenderSystem::Instance().Destroy();
    CollisionSystem::Instance().Destroy();
    SceneManager::Instance().Destroy();
    AssetManager::Instance().Destroy();
	
}

void Engine::GameLoop()
{
	UISystem::Instance().Start();
	if (gameStartCallback)
		gameStartCallback();
	while (!quit)
	{
        // PreUpdate TBD

		Time::Instance().Update();
        InputManager::Instance().Update();

		SceneManager::Instance().PreUpdate();

        SceneManager::Instance().Update();
        CollisionSystem::Instance().Update();
        RenderSystem::Instance().Update();
		UISystem::Instance().Update();

		SceneManager::Instance().LateUpdate();
        // PostUpdate TBD
		
		//leaking check
		//Debug::Log("Asset Manager : " + std::to_string(AssetManager::Instance().assets.size()));
		//Debug::Log("Render system : " + std::to_string(RenderSystem::Instance().GetRenderableSize()));
		//Debug::Log("Collision system : " + std::to_string(CollisionSystem::Instance().colliders.size()));
		//Debug::Log("Scene Manager : " + std::to_string(SceneManager::Instance().currentScene->entities.size()));
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
