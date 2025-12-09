#ifndef _SCENE_H_
#define _SCENE_H_

#include "Object.h"

class Entity;
class Engine;
class SceneManager;

class Scene final : public Object
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Scene, Object)

public:
	Entity* CreateEntity(const std::vector<std::string>& component_list);

	void AddEntity(Entity* e);
	const std::string& GetName() const { return name; }
	void SetName(const std::string& _name) { name = _name; }
	Entity* FindEntityByName(const std::string& entityName);
	std::vector<Entity*> FindAllEntitiesByTag(const std::string& tag);
	void RemoveEntity(Entity* e);

	void CleanScene();

private:
	void Initialize();
	void Load(json::JSON& jsonData) override;
	void Start();
	void PreUpdate();
	void Update();
	void LateUpdate();
	void Destroy();
	
	std::string GetUniqueName(const std::string& candidateName);

private:
	std::string name;
	std::list<Entity*> entities;
	std::list<Entity*> entities_to_remove;
	std::list<Entity*> entities_to_add;
	friend class Engine;
	friend class SceneManager;

};

#endif