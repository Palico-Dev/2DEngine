#include "GameCore.h"
#include "GameController.h"
#include "DataBindingRegistry.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Entity.h"
#include "Transform.h"
#include "FileManager.h"
#include "NetworkEngine.h"
#include "Engine.h"
#include "AssetManager.h"
#include "Random.h"
#include "NetworkComponent.h"
#include "UISystem.h"
#include "Widget.h"

void GameController::Init()
{
	auto& registry = DataBindingRegistry::Instance();

	//registry.RegisterString(GetHashCode("FPS"), []()
	//	{
	//		return std::to_string(Time::Instance().FPS());
	//	});

	if (Engine::Instance().GetRole() == EngineRole::Server)
	{
		playerJoinedCallback = std::bind(&GameController::OnPlayerJoined, this,
			std::placeholders::_1, std::placeholders::_2);
		NetworkEngine::Instance().RegisterPacketCallback(ID_NEW_INCOMING_CONNECTION, &playerJoinedCallback);
	}

	if (Engine::Instance().GetRole() == EngineRole::Client)
	{
		msgCallback = std::bind(&GameController::OnReceiveMsg, this,
			std::placeholders::_1, std::placeholders::_2);
		NetworkEngine::Instance().RegisterPacketCallback(ID_MSG, &msgCallback);
	}

	playerPrefab = AssetManager::Instance().GetAsset<PrefabAsset>("player.prefab");

}

void GameController::Start()
{

}

void GameController::Serialize(json::JSON& j)
{

}

void GameController::Deserialize(json::JSON& j)
{

}

void GameController::GameOver()
{
	NetworkEngine::Instance().SendMessage("GameOver");
	NetworkEngine::Instance().KickAllClients();
	Engine::Instance().SetGamePause(true);
}

void GameController::OnPlayerJoined(RakNet::BitStream& _bStream, RakNet::RakNetGUID& guid)
{
	Debug::Log("[Game Controller] Player joined");
	Entity* newPlayer = Gameplay::Spawn(playerPrefab,Random::Vec2(50.0f,700.0f,750.0f,751.0f));
	players.push_back(newPlayer);
	AllocateAuthority(newPlayer, guid);

	if (players.size() >= 2)
	{
		isGameStarted = true;
		NetworkEngine::Instance().SendMessage("GameStart");
	}
}

void GameController::AllocateAuthority(Entity* player, RakNet::RakNetGUID& guid)
{
	unsigned int networkId = player->GetComponent<NetworkComponent>()->networkId;
	RakNet::BitStream bStream;
	bStream.Write((unsigned char)NetworkPacketIds::ID_ALLOCATE_AUTHORITY);
	bStream.Write(networkId);
	NetworkEngine::Instance().SendPacket(bStream, &guid);
}

void GameController::OnReceiveMsg(RakNet::BitStream& _bStream, RakNet::RakNetGUID& guid)
{
	RakNet::RakString rakString;
	_bStream.Read(rakString);
	
	std::string msg = rakString.C_String();
	
	if (msg == "GameOver")
	{
		OnReceiveGameOver();
	}
	else if(msg == "GameStart")
	{
		OnReceiveGameStart();
	}
}

void GameController::OnReceiveGameOver()
{
	Debug::Log("GAME OVER!!!");
	isGameStarted = false;
	Widget* w = UISystem::Instance().FindWidgetByName("GameOverWidget");
	w->SetVisibility(WidgetVisibility::Visable);
	Engine::Instance().SetGamePause(true);
}

void GameController::OnReceiveGameStart()
{
	isGameStarted = true;
}

