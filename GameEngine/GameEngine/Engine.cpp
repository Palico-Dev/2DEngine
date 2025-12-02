#include "EngineCore.h"
#include "Engine.h"
#include "InputManager.h"
#include "RenderSystem.h"
#include "CollisionSystem.h"
#include "AssetManager.h"
#include "SceneManager.h"

extern void Engine_Register();

void Engine::Initialize()
{
    Engine_Register();

	LoadGameSettings("GameSettings.json");

	Time::Instance().Initialize();
    RenderSystem::Instance().Initialize();
    InputManager::Instance().Initialize();
    CollisionSystem::Instance().Initialize();
    AssetManager::Instance().Initialize();
    SceneManager::Instance().Initialize();
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

void Engine::LoadGameSettings(const std::string& filePath)
{
	std::ifstream file(filePath);
	M_ASSERT(file.is_open(), ("Failed to open game settings file: " + filePath).c_str());

	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string content = buffer.str();
	json::JSON root = json::JSON::Load(content);

    if (root.hasKey("Scenes")) {
		json::JSON scenesJson = root.at("Scenes");
		SceneManager& sceneManager = SceneManager::Instance();
        for (auto& sceneEntry : scenesJson.ArrayRange()) {
			sceneManager.RegisterScene(
                sceneEntry.at("SceneName").ToString(), 
                sceneEntry.at("FilePath").ToString()
            );
        }
    }

    if(root.hasKey("StartupScene")) {
        SceneManager::Instance().SetStartupScene(root.at("StartupScene").ToString());
	}
}
