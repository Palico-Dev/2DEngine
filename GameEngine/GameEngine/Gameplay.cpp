#include "EngineCore.h"
#include "Gameplay.h"
#include "PrefabAsset.h"
#include "Entity.h"
#include "SceneManager.h"
#include "Scene.h"
#include "Transform.h"

Entity* Gameplay::Spawn(PrefabAsset* prefab)
{
	Entity* e = prefab->GetPrefab();
	Entity* res = e->Clone();
	SceneManager::Instance().GetCurrentScene()->AddEntity(res);
	res->Initialize();
	return res;
}

Entity* Gameplay::Spawn(PrefabAsset* prefab, glm::vec2 pos)
{
	Debug::Log("Spawn prefab");
	Entity* clone = Spawn(prefab);
	if (clone->GetComponent<Transform>())
	{
		clone->GetComponent<Transform>()->SetPosition(pos);
	}
	return clone;
}

void Gameplay::Destroy(Entity* e)
{

}

Entity* Gameplay::FindEntityWithName(const std::string& name)
{
	return SceneManager::Instance().GetCurrentScene()->FindEntityByName(name);
}

std::vector<Entity*> Gameplay::FindAllEntitiesWithTag(const std::string& tag)
{
	return SceneManager::Instance().GetCurrentScene()->FindAllEntitiesByTag(tag);
}


