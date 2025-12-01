#include "EngineCore.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "AssetManager.h"

void SceneManager::Initialize()
{

	isInitialized = true;
	
	if(!startupSceneName.empty())
	{
		SetActiveScene(startupSceneName);
	}
	
}

void SceneManager::Update()
{
	Scene* prevActiveScene = activeScene;
	if(!isInitialized)
	{
		return;
	}

	if(queuedActiveScene)
	{
		activeScene = queuedActiveScene;
		queuedActiveScene = nullptr;
		if(prevActiveScene && prevActiveScene != activeScene)
		{
			for(auto& rec : sceneRecords)
			{
				if(rec.instance == prevActiveScene)
				{
					DEBUG_LOG(2, "Destroying previous active scene: " + rec.name);
					prevActiveScene->Destroy();
					delete prevActiveScene;
					rec.instance = nullptr;
					break;
				}
			}
		}
	}

	if(activeScene)
	{
		activeScene->Update();
	}
}

void SceneManager::Destroy()
{
	if(!isInitialized)
	{
		return;
	}

	for(auto&rec : sceneRecords)
	{
		if(rec.instance)
		{
			rec.instance->Destroy();
			delete rec.instance;
			rec.instance = nullptr;
		}
	}

	activeScene = nullptr;
	queuedActiveScene = nullptr;
	isInitialized = false;
}

void SceneManager::RegisterScene(const std::string& name, const std::string& filePath)
{
	SceneRecord record;
	record.name = name;
	record.filePath = filePath;
	record.instance = nullptr;
	sceneRecords.push_back(record);
}

void SceneManager::SetActiveScene(const std::string& name)
{
	SceneRecord* record = FindSceneRecordByName(name);
	if(!record)
		return;
	
	if(record)
	{
		Scene* scene = LoadSceneFromRecord(*record);
		if (!scene)
			return;
		
		activeScene = scene;
	}
}

void SceneManager::QueueActiveScene(const std::string& name)
{
	SceneRecord* record = FindSceneRecordByName(name);
	if(!record)
		return;
	Scene* scene = LoadSceneFromRecord(*record);
	if (!scene)
		return;
	queuedActiveScene = scene;
}

SceneRecord* SceneManager::FindSceneRecordByName(const std::string& name)
{
	for(auto& record : sceneRecords)
	{
		if(record.name == name)
		{
			return &record;
		}
	}
	return nullptr;
}

Scene* SceneManager::LoadSceneFromRecord(SceneRecord& record)
{
	if(record.instance)
	{
		return record.instance;
	}

	Scene* scene = static_cast<Scene*>(CreateObject("Scene"));
	if(!scene)
	{
		return nullptr;
	}

	scene->SetName(record.name);
	std::string sceneName = scene->GetName();

	std::ifstream file(record.filePath);
	M_ASSERT(file.is_open(), ("Failed to open game settings file: " + record.filePath).c_str());

	std::stringstream buffer;
	buffer << file.rdbuf();
	std::string content = buffer.str();
	json::JSON root = json::JSON::Load(content);

	if (root.hasKey("assets"))
	{
		AssetManager::Instance().Load(root, sceneName);
	}

	if (root.hasKey("scene")) {
		json::JSON scenesJson = root.at("scene");
		scene->Load(scenesJson);
		scene->Initialize();
		record.instance = scene;
	}

	return scene;
}

