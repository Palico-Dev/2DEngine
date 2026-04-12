#pragma once
#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "Component.h"

class Entity;

class GameController
{
	DECLARE_SINGLETON(GameController);


public:
	void Init();
	void Start();

	void Serialize(json::JSON& j);
	void Deserialize(json::JSON& j);

	void GameOver();

public:
	bool isGameStarted = false;

private:
	void ButtonTest();
	void ResumeGame();

	void OnPlayerJoined(RakNet::BitStream& _bStream, RakNet::RakNetGUID& guid);
	void AllocateAuthority(Entity* player, RakNet::RakNetGUID& guid);

	void OnReceiveMsg(RakNet::BitStream& _bStream, RakNet::RakNetGUID& guid);
	void OnReceiveGameOver();
	void OnReceiveGameStart();

private:
	PrefabAsset* playerPrefab = nullptr;

	std::function<void(RakNet::BitStream& _bitStream, RakNet::RakNetGUID& guid)> playerJoinedCallback;
	std::function<void(RakNet::BitStream& _bitStream, RakNet::RakNetGUID& guid)> msgCallback;

	std::vector<Entity*> players;
};

#endif


