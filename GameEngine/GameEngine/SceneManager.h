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
	void LoadScene(const char* path);

private:
	void Initialize();
	void Update();
	void Destroy();
	void Start();

private:
	friend class Engine;

	std::list<Scene*> scenes;

};

#endif //_SCENEMANAGER_H_