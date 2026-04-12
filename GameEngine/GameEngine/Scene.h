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

	void NetworkSerializeSpawnPrefab(Entity* entity, RakNet::BitStream& _bStream) const;
	void NetworkSerializeDestroyEntity(Entity* entity, RakNet::BitStream& _bStream) const;

private:
	void Initialize();
	void Load(json::JSON& jsonData) override;
	void Start();
	void PreUpdate();
	void Update();
	void LateUpdate();
	void Destroy();
	
	std::string GetUniqueName(const std::string& candidateName);

protected:
	void NetworkSerialize(RakNet::BitStream& _bStream)const override;
	void NetworkDeserialize(RakNet::BitStream& _bStream) override;

	void NetworkDeserializeSpawnPrefab(RakNet::BitStream& _bStream);

	void NetworkDeserializeDestroyEntity(RakNet::BitStream& _bStream);

	void NetworkSerializeSnapShot(RakNet::BitStream& _bStream) const;
	void NetworkDeserializeSnapShot(RakNet::BitStream& _bStream);

	void InvokeRPC(RakNet::BitStream& bitStream);

private:
	std::string name;
	std::list<Entity*> entities;
	std::list<Entity*> entities_to_remove;
	std::list<Entity*> entities_to_add;
	std::unordered_map<unsigned int, Entity*> networkEntities;
	friend class Engine;
	friend class SceneManager;
	friend class SaveManager;

};

#endif