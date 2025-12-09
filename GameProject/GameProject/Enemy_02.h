#pragma once
#ifndef _ENEMY02_H_
#define _ENEMY02_H_

#include "Enemy.h"

class PrefabAsset;

class Enemy_02 : public Enemy
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Enemy_02, Enemy)
	CLONEABLE(Enemy_02);


public:
	void Start() override;
	void Update() override;
	void Load(json::JSON& jsonData) override;

private:
	void OnTriggerEnter(Collider* other) override;

	float moveRight = 1.0f;
};


#endif

