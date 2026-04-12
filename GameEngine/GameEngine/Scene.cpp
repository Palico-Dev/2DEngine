#include "EngineCore.h"
#include "Scene.h"
#include "Entity.h"
#include "AssetManager.h"
#include "FileManager.h"
#include "PrefabAsset.h"
#include "Transform.h"
#include "Utility.h"
#include "NetworkComponent.h"

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
		for (auto& entityJson : entitiesJson.ArrayRange())
		{
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

		if (entity->HasComponent<NetworkComponent>())
		{
			unsigned int networkId = entity->GetComponent<NetworkComponent>()->networkId;
			if (networkId == 0)
				Debug::Error("The Network Object doesn't have a Network ID!");
			networkEntities[networkId] = entity;
		}
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
	for (auto& entity : entities_to_remove)
	{
		if (entity->HasComponent<NetworkComponent>())
		{
			unsigned int networkId = entity->GetComponent<NetworkComponent>()->networkId;
			networkEntities.erase(networkId);
			Debug::Log("[Gameplay] Removed network entity with ID: " + std::to_string(networkId));
		}

		entity->Destroy();
		entities.remove(entity);
		entities_to_add.remove(entity);

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

		if (FindEntityByName(newName.c_str()) == nullptr)
		{
			return newName;
		}
		i++;
	}
}

void Scene::NetworkSerialize(RakNet::BitStream& _bStream) const
{
	_bStream.Write((unsigned int)networkEntities.size());

	for (const auto& [netId, entity] : networkEntities)
	{
		_bStream.Write(netId);
		entity->NetworkSerialize(_bStream);
	}
}

void Scene::NetworkDeserialize(RakNet::BitStream& _bStream)
{
	unsigned int count = 0;
	_bStream.Read(count);

	for (unsigned int i = 0; i < count; ++i)
	{
		unsigned int netId = 0;
		_bStream.Read(netId);

		auto it = networkEntities.find(netId);
		if (it != networkEntities.end())
		{
			Entity* entity = it->second;
			entity->NetworkDeserialize(_bStream);
		}
	}
}

void Scene::NetworkSerializeSpawnPrefab(Entity* entity, RakNet::BitStream& _bStream) const
{
	NetworkComponent* netComp = entity->GetComponent<NetworkComponent>();

	_bStream.Write(netComp->networkId);

	RakNet::RakString rakString(netComp->prefabName.c_str());
	_bStream.Write(rakString);

	entity->NetworkSerialize(_bStream);
}

void Scene::NetworkDeserializeSpawnPrefab(RakNet::BitStream& _bStream)
{
	unsigned int netId = 0;
	RakNet::RakString prefabString;

	_bStream.Read(netId);
	_bStream.Read(prefabString);

	std::string prefabName = prefabString.C_String();

	PrefabAsset* prefab = AssetManager::Instance().GetAsset<PrefabAsset>(prefabName);

	if (prefab != nullptr)
	{
		Entity* newEntity = Gameplay::Spawn(prefab);

		newEntity->GetComponent<NetworkComponent>()->networkId = netId;

		newEntity->NetworkDeserialize(_bStream);

		Debug::Log("[Network] Client spawned prefab: " + prefabName + " with network ID: " + std::to_string(netId));
	}
	else
	{
		Debug::Error("[Network] Client failed to spawn prefab. Asset not found: " + prefabName);

	}
}

void Scene::NetworkSerializeDestroyEntity(Entity* entity, RakNet::BitStream& _bStream) const
{
	_bStream.Write(entity->GetComponent<NetworkComponent>()->networkId);
}

void Scene::NetworkDeserializeDestroyEntity(RakNet::BitStream& _bStream)
{
	unsigned int netId = 0;
	_bStream.Read(netId);

	auto it = networkEntities.find(netId);
	if (it != networkEntities.end())
	{
		Entity* entity = it->second;
		RemoveEntity(entity);
	}
}

void Scene::NetworkSerializeSnapShot(RakNet::BitStream& _bStream) const
{
	_bStream.Write((unsigned int)networkEntities.size());

	for (const auto& [netId, entity] : networkEntities)
	{
		NetworkComponent* netComp = entity->GetComponent<NetworkComponent>();

		_bStream.Write(netId);

		RakNet::RakString rakString(netComp->prefabName.c_str());
		_bStream.Write(rakString);

		entity->NetworkSerialize(_bStream);
	}
}

void Scene::NetworkDeserializeSnapShot(RakNet::BitStream& _bStream)
{
	unsigned int count = 0;
	_bStream.Read(count);

	for (unsigned int i = 0; i < count; ++i)
	{
		unsigned int netId = 0;
		_bStream.Read(netId);

		RakNet::RakString rakString;
		_bStream.Read(rakString);
		std::string prefabName = rakString.C_String();

		PrefabAsset* prefab = AssetManager::Instance().GetAsset<PrefabAsset>(prefabName);

		if (prefab == nullptr)
		{
			Debug::Error("Prefab not found: " + prefabName);
		}

		Entity* newEntity = Gameplay::Spawn(prefab);

		newEntity->GetComponent<NetworkComponent>()->networkId = netId;
		networkEntities[netId] = newEntity;

		newEntity->NetworkDeserialize(_bStream);
	}
}

void Scene::InvokeRPC(RakNet::BitStream& bitStream)
{
	unsigned int netId = 0;
	STRCODE rpcHash = 0;

	bitStream.Read(netId);
	bitStream.Read(rpcHash);

	auto it = networkEntities.find(netId);
	if (it != networkEntities.end())
	{
		Entity* targetEntity = it->second;
		NetworkComponent* netComp = targetEntity->GetComponent<NetworkComponent>();

		auto rpcIterator = netComp->rpcRegistry.find(rpcHash);

		if (rpcIterator != netComp->rpcRegistry.end())
		{
			rpcIterator->second(bitStream);
		}
		else
		{
			Debug::Warning("[Network] RPC Hash not registered on Entity: " + targetEntity->name);
		}
	}
	else
	{
		Debug::Warning("[Network] Received RPC for unknown NetworkID: " + std::to_string(netId));
	}
}

Entity* Scene::CreateEntity(const std::vector<std::string>& component_list)
{
	Entity* new_entity = static_cast<Entity*>(CreateObject("Entity"));

	if (new_entity)
	{
		for (std::string comp : component_list)
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
	for (auto& e : entities_to_add)
	{
		if (e->HasTag(tag))
			res.push_back(e);
	}
	return res;
}

void Scene::RemoveEntity(Entity* e)
{
	if (!Utility::ListContains<Entity*>(entities_to_remove, e))
		entities_to_remove.push_back(e);
}

void Scene::CleanScene()
{
	for (auto& e : entities)
	{
		if (!e->HasTag("DontDestroyOnLoad"))
			Gameplay::Destroy(e);
	}
}
