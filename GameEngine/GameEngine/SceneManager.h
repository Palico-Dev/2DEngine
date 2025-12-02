#pragma once

#ifndef _SCENEMANAGER_H_
#define _SCENEMANAGER_H_


class Scene;
class Engine;

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
	void RegisterScene(const std::string& name, const std::string& filePath);
	void SetStartupScene(const std::string& name) { startupSceneName = name; }

	Scene* GetActiveScene() { return activeScene; }	
	
	void QueueActiveScene(const std::string& name);


private:
	void Initialize();
	void Update();
	void Destroy();
	void Start();

private:
	friend class Engine;
	Scene* activeScene = nullptr;
	Scene* queuedActiveScene = nullptr;
	bool isInitialized = false;

	 
	std::vector<SceneRecord> sceneRecords;
	std::string startupSceneName;

	
	SceneRecord* FindSceneRecordByName(const std::string& name);
	Scene* LoadSceneFromRecord(SceneRecord& record);
	void SetActiveScene(const std::string& name);
};

#endif //_SCENEMANAGER_H_