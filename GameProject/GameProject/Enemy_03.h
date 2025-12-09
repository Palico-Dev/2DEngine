#pragma once
#ifndef _ENEMY03_H_
#define _ENEMY03_H_

#include "Enemy.h"

class PrefabAsset;

class Enemy_03 : public Enemy
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Enemy_03, Enemy)
	CLONEABLE(Enemy_03);

public:
	void Start() override;
	void Update() override;
	void Load(json::JSON& jsonData) override;
	


private:
	void OnTriggerEnter(Collider* other) override;
	void Shoot() override;
};


#endif

