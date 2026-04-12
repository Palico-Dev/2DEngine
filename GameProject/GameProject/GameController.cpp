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

void GameController::Init()
{
	auto& registry = DataBindingRegistry::Instance();

	if (Engine::Instance().GetRole() == EngineRole::Server)
	{
		playerJoinedCallback = std::bind(&GameController::OnPlayerJoined, this,
			std::placeholders::_1, std::placeholders::_2);
		NetworkEngine::Instance().RegisterPacketCallback(ID_NEW_INCOMING_CONNECTION, &playerJoinedCallback);
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

void GameController::OnPlayerJoined(RakNet::BitStream& _bStream, RakNet::RakNetGUID& guid)
{
	Debug::Log("[Game Controller] Player joined");
	Entity* newPlayer = Gameplay::Spawn(playerPrefab,Random::Vec2(50.0f,300.0f,300.0f,600.0f));
	players.push_back(newPlayer);
	AllocateAuthority(newPlayer, guid);

	if (!isGameStarted && players.size() >= 2)
	{
		//isGameStarted = true;
		Debug::Log("[Gameplay] Game Start!!!");
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

