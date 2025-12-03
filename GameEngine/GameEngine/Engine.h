#pragma once

#ifndef _ENGINE_H_
#define _ENGINE_H_

class Engine final
{

	DECLARE_SINGLETON(Engine)
public:
	void Initialize();
	void Destroy();
	void GameLoop();

	json::JSON GetGameSettings() { return gameSettings; }

private:
	void LoadGameSettings();

	bool quit = false;
	friend class InputManager;

private:
	json::JSON gameSettings;
};

#endif