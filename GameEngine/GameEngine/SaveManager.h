#pragma once
#ifndef _SAVEMANAGER_H_
#define _SAVEMANAGER_H_

class SaveManager
{
	DECLARE_SINGLETON(SaveManager);

public:
	void SaveGame();
	void LoadGame();
	void SetGameSerialize(std::function<void(json::JSON&)> callback) { gameCallback = callback; }

private:
	void Serialize(json::JSON& j);
	void Deserialize(json::JSON& j);

private:
	std::function<void(json::JSON&)> gameCallback;
};

#endif


