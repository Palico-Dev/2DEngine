#pragma once

#ifndef _ENGINE_H_
#define _ENGINE_H_

enum class EngineRole
{
	Client,
	Server,
	Standalone
};

class Engine final
{

	DECLARE_SINGLETON(Engine)
public:
	void Initialize(EngineRole _role = EngineRole::Standalone);
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

	EngineRole GetRole()
	{
		return role;
	}

	void SetGamePause(bool p) { pause = p; }
	void ToggleGamePause() { pause = !pause; }

private:
	void LoadGameSettings();
	friend class InputManager;
	void LogRole();

private:
	json::JSON gameSettings;
	bool quit = false;
	bool pause = false;

	EngineRole role = EngineRole::Standalone;

	std::function<void()> gameInitCallback = nullptr;
	std::function<void()> gameStartCallback = nullptr;
};

#endif