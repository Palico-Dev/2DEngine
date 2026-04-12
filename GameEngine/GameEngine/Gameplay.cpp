#include "EngineCore.h"
#include "Gameplay.h"
#include "PrefabAsset.h"
#include "Entity.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Transform.h"
#include "Engine.h"
#include "NetworkComponent.h"
#include "NetworkEngine.h"

namespace
{
	Entity* LocalSpawn(PrefabAsset* prefab)
	{
		Entity* e = prefab->GetPrefab();
		Entity* res = e->Clone();
		SceneManager::Instance().GetCurrentScene()->AddEntity(res);
		res->Initialize();
		Debug::Log("[Gameplay] Spawn prefab: " + res->name);
		return res;
	}

	void BroadcastSpawn(Entity* e)
	{
		if (Engine::Instance().GetRole() == EngineRole::Server)
		{
			if (e->HasComponent<NetworkComponent>())
			{
				NetworkComponent* netComp = e->GetComponent<NetworkComponent>();
				netComp->networkId = NetworkEngine::Instance().GenerateNetworkId();;

				RakNet::BitStream bitStream;
				bitStream.Write((unsigned char)NetworkPacketIds::ID_SCENE_MANAGER);
				bitStream.Write((unsigned char)NetworkPacketIds::ID_SPAWN_PREFAB);
				SceneManager::Instance().GetCurrentScene()->NetworkSerializeSpawnPrefab(e, bitStream);
				NetworkEngine::Instance().SendPacket(bitStream);
				Debug::Log("[Network] Sent spawn packet for networkID: " + std::to_string(netComp->networkId) + " entity: " + e->name);
			}
			else
			{
				Debug::Warning("[Network] Spawned entity does not have NetworkComponent, it will not be replicated to clients: " + e->name);
			}
		}
	}
}

Entity* Gameplay::Spawn(PrefabAsset* prefab)
{
	Entity* e = LocalSpawn(prefab);

	BroadcastSpawn(e);

	return e;
}

void Gameplay::Spawn(Entity* entity)
{
	SceneManager::Instance().GetCurrentScene()->AddEntity(entity);
	entity->Initialize();
}

Entity* Gameplay::Spawn(PrefabAsset* prefab, glm::vec2 pos)
{
	Entity* clone = LocalSpawn(prefab);
	if (clone->GetComponent<Transform>())
	{
		clone->GetComponent<Transform>()->SetPosition(pos);
	}
	BroadcastSpawn(clone);
	return clone;
}

void Gameplay::Destroy(Entity* e)
{
	Debug::Log("[Gameplay] Destroy entity:"+ e->name);
	SceneManager::Instance().GetCurrentScene()->RemoveEntity(e);

	if (Engine::Instance().GetRole() == EngineRole::Server)
	{
		if (e->HasComponent<NetworkComponent>())
		{
			RakNet::BitStream bitStream;
			bitStream.Write((unsigned char)NetworkPacketIds::ID_SCENE_MANAGER);
			bitStream.Write((unsigned char)NetworkPacketIds::ID_DESTROY_ENTITY);
			SceneManager::Instance().GetCurrentScene()->NetworkSerializeDestroyEntity(e, bitStream);
			NetworkEngine::Instance().SendPacket(bitStream);
			Debug::Log("[Network] Sent destroy packet for networkID: " + std::to_string(e->GetComponent<NetworkComponent>()->networkId) + " entity: " + e->name);
		}
	}
}

Entity* Gameplay::FindEntityWithName(const std::string& name)
{
	return SceneManager::Instance().GetCurrentScene()->FindEntityByName(name);
}

std::vector<Entity*> Gameplay::FindAllEntitiesWithTag(const std::string& tag)
{
	return SceneManager::Instance().GetCurrentScene()->FindAllEntitiesByTag(tag);
}



