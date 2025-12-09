#pragma once
#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "Component.h"

class GameController
{
	DECLARE_SINGLETON(GameController);


public:
	void Init();
	void LoseHealth();
	void RestartGame();
	
	void AddScore(int add);
	int GetScore() { return score; }
	int GetHighestScore() { return highestScore; }

private:
	int highestScore = 0;
	int score = 0;
};

#endif


