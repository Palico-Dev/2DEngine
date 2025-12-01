#include "EngineCore.h"
#include "Scene.h"
#include "Entity.h"
#include "AssetManager.h"

IMPLEMENT_DYNAMIC_CLASS(Scene)

void Scene::Initialize()
{
	Object::Initialize();

	for (auto& entity : entities)
	{
		entity->Initialize();
	}
	DEBUG_LOG(2, "Initialized Scene: " + name);
}

void Scene::Load(json::JSON& jsonData)
{
	Object::Load(jsonData);

	if (jsonData.hasKey("entities"))
	{
		json::JSON entitiesJson = jsonData.at("entities");
		for (auto& entityItem : entitiesJson.ArrayRange()) {
			Entity* newEntity = static_cast<Entity*>(CreateObject("Entity"));
			newEntity->Load(entityItem);
			if(newEntity->GetTransform() == nullptr)
			{
				// Ensure every Entity has a Transform
				newEntity->CreateComponent("Transform");
			}
			newEntity->Initialize();
			entities.push_back(newEntity);
		}
	}
}
 
void Scene::Update()
{
	for (auto& entity : entities)
	{
		if (entity->GetLifeState() != EntityLifeState::Alive) continue;
		entity->Update();
	}

	// Deal with removals
	for (auto it = entities.begin(); it != entities.end(); ) {
		Entity* entity = *it;
		if (entity->GetLifeState() == EntityLifeState::PendingDestroy ||
			entity->GetLifeState() == EntityLifeState::Destroyed) {

			entity->Destroy();
			delete entity;
			it = entities.erase(it);
		}
		else {
			++it;
		}
	}
}

void Scene::Destroy()
{
	DEBUG_LOG(2, "Destroying Scene: " + name);
	Object::Destroy();

	for (auto& entity : entities)
	{
		entity->Destroy();
		delete entity;
	}
	entities.clear();

	AssetManager::Instance().Unload(name);
}

Entity* Scene::CreateEntity(const std::vector<std::string>& component_list)
{
	Entity* new_entity = static_cast<Entity*>(CreateObject("Entity"));
	
	if (new_entity)
	{
		for(std::string comp : component_list)
		{
			new_entity->CreateComponent(comp);			
		}
		new_entity->Initialize();
		entities.push_back(new_entity);
		return new_entity;
	}
	return nullptr;
}
