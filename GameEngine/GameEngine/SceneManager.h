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