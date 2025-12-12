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


};

#endif


