#ifndef _SCENE_H_
#define _SCENE_H_

#include "Object.h"

class Entity;
class Engine;
class SceneManager;
class Scene final : public Object
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Scene, Object)
private:
	std::string name;
	std::list<Entity*> entities;
	std::list<Entity*> entities_to_remove;
	friend class Engine;
	friend class SceneManager;

private:
	void Initialize();
	void Load(json::JSON& jsonData) override;
	void Update();
	void Destroy();
	

public:
	/// <summary>
	/// Create an Entity with the given list of Component type names.
	/// </summary>
	/// <param name="component_list"></param>
	/// <returns></returns>
	Entity* CreateEntity(const std::vector<std::string>& component_list);

	const std::string& GetName() const { return name; }
	void SetName(const std::string& _name) { name = _name; }
};

#endif //!_SCENE_H_