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
	void LoseHealth();
	void Start();
	void RestartGame();
	
	void AddScore(int add);
	int GetScore() { return score; }
	int GetHighestScore() { return highestScore; }

	void Serialize(json::JSON& j);
	void Deserialize(json::JSON& j);

private:
	int highestScore = 0;
	int score = 0;

	int gameHealth = 3;

	Entity* player = nullptr;
};

#endif


