#pragma once
#ifndef _SAVEMANAGER_H_
#define _SAVEMANAGER_H_

class SaveManager
{
	DECLARE_SINGLETON(SaveManager);

public:
	void SaveGame();
	void LoadGame();
	void SetGameSerialize(std::function<void(json::JSON&)> callback) { gameSerializeCallback = callback; }
	void SetGameDeserialize(std::function<void(json::JSON&)> callback) { gameDeserializeCallback = callback; }

private:
	void Serialize(json::JSON& j);
	void Deserialize(json::JSON& j);

private:
	std::function<void(json::JSON&)> gameSerializeCallback;
	std::function<void(json::JSON&)> gameDeserializeCallback;
};

#endif


