#pragma once
#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_

class Scene;
class Engine;
class PrefabAsset;

class SceneRecord {
public:
	std::string name;
	std::string filePath;
	Scene* instance = nullptr;
};

class SceneManager final
{
	DECLARE_SINGLETON(SceneManager)

public:
	void LoadScene(const char* path);
	Scene* GetCurrentScene() { return currentScene; }
	void RequestSnapshot();

protected:
	void NetworkUpdate();
	void SerializeSnapshot(RakNet::RakNetGUID* guid = nullptr) const;
	void ProcessPacket(RakNet::BitStream& _bStream, RakNet::RakNetGUID& guid);
	void NetworkConnection(RakNet::BitStream& _bStream, RakNet::RakNetGUID& guid);

	std::function<void(RakNet::BitStream& _bitStream, RakNet::RakNetGUID& guid)> IncommingConnectionCallback;
	std::function<void(RakNet::BitStream& _bitStream, RakNet::RakNetGUID& guid)> ProcessPacketCallback;

private:
	void Initialize();
	void Update();
	void Destroy();
	void Start();
	void LateUpdate();
	void PreUpdate();

private:
	friend class Engine;

	std::list<Scene*> scenes;

	Scene* currentScene;

};


#endif //_SCENEMANAGER_H_