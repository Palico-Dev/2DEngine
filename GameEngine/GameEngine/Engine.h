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

	void SetGameInitCallback(std::function<void()> callback)
	{
		gameInitCallback = callback;
	}

private:
	void LoadGameSettings();
	friend class InputManager;

private:
	json::JSON gameSettings;
	bool quit = false;
	std::function<void()> gameInitCallback = nullptr;
};

#endif