#include "EngineCore.h"
#include "Scene.h"
#include "Entity.h"
#include "AssetManager.h"
#include "FileManager.h"
#include "PrefabAsset.h"
#include "Transform.h"

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
		for (auto& entityJson : entitiesJson.ArrayRange()) {
			std::string type = FileManager::JsonReadString(entityJson, "type");
			if (type == "Prefab")
			{
				std::string assetName = FileManager::JsonReadString(entityJson, "asset");
				PrefabAsset* asset = AssetManager::Instance().GetAsset<PrefabAsset>(assetName);
				Entity* newEntity = asset->GetPrefab()->Clone();

				glm::vec2 pos = FileManager::JsonReadVec2(entityJson, "position");
				if (newEntity->transform != nullptr)
				{
					newEntity->transform->SetPosition(pos);
				}

				newEntity->Initialize();
				AddEntity(newEntity);
				
			}
			else if (type == "Entity")
			{
				Entity* newEntity = (Entity*)(CreateObject("Entity"));
				newEntity->Load(entityJson);

				newEntity->Initialize();
				AddEntity(newEntity);

			}

		}
	}
}
 
void Scene::Start()
{
	for (auto& entity : entities)
	{
		entity->Start();
	}
}

void Scene::PreUpdate()
{
	if (entities_to_add.empty())
		return;
	for (auto& entity : entities_to_add)
	{
		entity->Start();
		entities.push_back(entity);
	}
	entities_to_add.clear();
}

void Scene::Update()
{
	for (auto& entity : entities)
	{
		entity->Update();
	}

}

void Scene::LateUpdate()
{
	for (auto entity : entities_to_remove)
	{
		entity->Destroy();
		entities.remove(entity);
		delete entity;
	}
	entities_to_remove.clear();
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

std::string Scene::GetUniqueName(const std::string& candidateName)
{
	if (FindEntityByName(candidateName) == nullptr)
	{
		return candidateName;
	}
	std::string baseName = candidateName;
	int i = 1;
	while (true)
	{
		std::string newName = baseName + " (" + std::to_string(i) + ")";

		if (FindEntityByName(newName.c_str())==nullptr)
		{
			return newName;
		}
		i++;
	}
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
		AddEntity(new_entity);
		return new_entity;
	}
	return nullptr;
}

void Scene::AddEntity(Entity* e)
{
	entities_to_add.push_back(e);
	e->name = GetUniqueName(e->name.c_str());
}

Entity* Scene::FindEntityByName(const std::string& entityName)
{
	for (auto& e : entities)
	{
		if (e->name == entityName)
		{
			return e;
		}
	}
	return nullptr;
}

std::vector<Entity*> Scene::FindAllEntitiesByTag(const std::string& tag)
{
	std::vector<Entity*> res;
	for (auto& e : entities)
	{
		if (e->HasTag(tag))
			res.push_back(e);
	}
	return res;
}

void Scene::RemoveEntity(Entity* e)
{
	entities_to_remove.push_back(e);
}
