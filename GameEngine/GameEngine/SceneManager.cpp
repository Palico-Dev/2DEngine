#include "EngineCore.h"
#include "SceneManager.h"
#include "Scene.h"
#include "InputManager.h"
#include "AssetManager.h"
#include "Engine.h"
#include "FileManager.h"
#include "UISystem.h"
#include "Entity.h"
#include "NetworkEngine.h"

void SceneManager::Initialize()
{
	json::JSON gameSettings = Engine::Instance().GetGameSettings();

	if (Engine::Instance().GetRole() == EngineRole::Client)
	{
		ProcessPacketCallback = std::bind(&SceneManager::ProcessPacket, this,
			std::placeholders::_1, std::placeholders::_2);
		NetworkEngine::Instance().RegisterPacketCallback(ID_SCENE_MANAGER, &ProcessPacketCallback);
	}

	if (Engine::Instance().GetRole() == EngineRole::Server)
	{
		IncommingConnectionCallback = std::bind(&SceneManager::NetworkConnection, this,
			std::placeholders::_1, std::placeholders::_2);
		NetworkEngine::Instance().RegisterPacketCallback(ID_NEW_INCOMING_CONNECTION, &IncommingConnectionCallback);

		ProcessPacketCallback = std::bind(&SceneManager::ProcessPacket, this,
			std::placeholders::_1, std::placeholders::_2);
		NetworkEngine::Instance().RegisterPacketCallback(ID_SCENE_MANAGER, &ProcessPacketCallback);
	}

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
	for (auto& s : scenes)
	{
		s->Start();
	}
}



void SceneManager::LateUpdate()
{
	for (auto& s : scenes)
	{
		s->LateUpdate();
	}
}

void SceneManager::PreUpdate()
{
	for (auto& s : scenes)
	{
		s->PreUpdate();
	}
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

void SceneManager::NetworkUpdate()
{
	RakNet::BitStream bStream;
	bStream.Write((unsigned char)NetworkPacketIds::ID_SCENE_MANAGER);
	bStream.Write((unsigned char)NetworkPacketIds::ID_SCENE_UPDATE);
	currentScene->NetworkSerialize(bStream);

	NetworkEngine::Instance().SendPacket(bStream);
}

void SceneManager::SerializeSnapshot(RakNet::RakNetGUID* guid /*= nullptr*/) const
{
	RakNet::BitStream bStream;
	bStream.Write((unsigned char)NetworkPacketIds::ID_SCENE_MANAGER);
	bStream.Write((unsigned char)NetworkPacketIds::ID_SCENE_SNAPSHOT);
	currentScene->NetworkSerializeSnapShot(bStream);
	NetworkEngine::Instance().SendPacket(bStream, guid);
}

void SceneManager::ProcessPacket(RakNet::BitStream& _bStream, RakNet::RakNetGUID& guid)
{
	unsigned char packetId = 0;
	_bStream.Read(packetId);
	switch (packetId)
	{
		//case NetworkPacketIds::ID_SCENE_CHANGE:
		//{
		//	STRCODE sceneId = -1;
		//	_bStream.Read(sceneId);
		//	SceneManager::Instance().LoadSceneByID(sceneId);
		//	break;
		//}
	case NetworkPacketIds::ID_SCENE_UPDATE:
	{
		currentScene->NetworkDeserialize(_bStream);
		break;
	}

	case  NetworkPacketIds::ID_SPAWN_PREFAB:
	{

		currentScene->NetworkDeserializeSpawnPrefab(_bStream);
		break;
	}
	case NetworkPacketIds::ID_DESTROY_ENTITY:
	{
		currentScene->NetworkDeserializeDestroyEntity(_bStream);
		break;
	}
	case NetworkPacketIds::ID_SCENE_SNAPSHOT:
	{
		currentScene->NetworkDeserializeSnapShot(_bStream);
		break;
	}
	case NetworkPacketIds::ID_RPC:
	{
		currentScene->InvokeRPC(_bStream);
		break;
	}

	default:
		break;
	}
}

void SceneManager::NetworkConnection(RakNet::BitStream& _bStream, RakNet::RakNetGUID& guid)
{
	SceneManager::Instance().SerializeSnapshot(&guid);
}
