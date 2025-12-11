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
	void SetGameStartCallback(std::function<void()> callback)
	{
		gameStartCallback = callback;
	}

	void SetGamePause(bool p) { pause = p; }
	void ToggleGamePause() { pause = !pause; }

private:
	void LoadGameSettings();
	friend class InputManager;

private:
	json::JSON gameSettings;
	bool quit = false;
	bool pause = false;

	std::function<void()> gameInitCallback = nullptr;
	std::function<void()> gameStartCallback = nullptr;
};

#endif