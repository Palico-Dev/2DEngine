#pragma once
#ifndef _GAMEPLAY_H_
#define _GAMEPLAY_H_

class Entity;
class PrefabAsset;
namespace RakNet
{
	class BitStream;
}

namespace Gameplay
{
	Entity* Spawn(PrefabAsset* prefab);
	void Spawn(Entity* entity);
	Entity* Spawn(PrefabAsset* prefab, glm::vec2 pos);

	void Destroy(Entity* e);

	Entity* FindEntityWithName(const std::string& name);
	std::vector<Entity*> FindAllEntitiesWithTag(const std::string& tag);

	void SendRPC(Entity* targetEntity, const std::string& functionName, RakNet::BitStream& customData);

}

#endif

