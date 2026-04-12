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

public:
	bool isGameStarted = false;

private:
	void ButtonTest();
	void ResumeGame();

private:
	void OnPlayerJoined(RakNet::BitStream& _bStream, RakNet::RakNetGUID& guid);
	void AllocateAuthority(Entity* player, RakNet::RakNetGUID& guid);

private:
	PrefabAsset* playerPrefab = nullptr;

	std::function<void(RakNet::BitStream& _bitStream, RakNet::RakNetGUID& guid)> playerJoinedCallback;

	std::vector<Entity*> players;
};

#endif


