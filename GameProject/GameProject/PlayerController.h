#pragma once
#ifndef _PLAYERCONTROLLER_H_
#define _PLAYERCONTROLLER_H_
#include "Component.h"

class Entity;
class Collider;

class PlayerController : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(PlayerController, Component)

public:
	void GetDamage();

public:
	void Update() override;
	void Start() override;
	void Initialize() override;
	Component* Clone() override;
	void OnTriggerEnter(Collider* other) override;

public:
	float speed = 200.0f;

	std::vector<Entity*> entities;
	PrefabAsset* bulletAsset = nullptr;

	float maxHealth = 5;
	float health = 5;

private:
	void MovementBounds(glm::vec2& dir);
	void OnAllocateAuthority(RakNet::BitStream& _bStream, RakNet::RakNetGUID& guid);

	void RPC_Move(RakNet::BitStream& _bStream);
	void RPC_Shoot(RakNet::BitStream& _bStream);

private:
	bool hasAuthority = false;
	std::function<void(RakNet::BitStream& _bitStream, RakNet::RakNetGUID& guid)> allocateAuthorityCallback;

	glm::vec2 movement = glm::vec2(0, 0);



};

#endif


