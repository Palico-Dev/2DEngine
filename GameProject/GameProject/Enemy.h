#pragma once
#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Component.h"

class PrefabAsset;

class Enemy : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Enemy, Component)
	CLONEABLE(Enemy);

public:
	void GetDamage();

public:
	void Start() override;
	void Update() override;
	void Load(json::JSON& jsonData) override;

private:
	void Shoot();
	void OnTriggerEnter(Collider* other);

private:
	int maxHealth = 5;
	int health = maxHealth;
	float shootTimer = 0.0f;
	float shootInterval = 3.0f;
	float speed = 130.0f;
	PrefabAsset* bullet = nullptr;
};


#endif

