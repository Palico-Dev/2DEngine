#pragma once

#ifndef _ENGINE_H_
#define _ENGINE_H_

class Engine final
{
	friend class InputManager;

public:
	void Initialize();
	void Destroy();
	void GameLoop();

private:
	void GetInput();

	bool quit = false;

	void LoadGameSettings(const std::string& filePath);

	DECLARE_SINGLETON(Engine)
};

#endif