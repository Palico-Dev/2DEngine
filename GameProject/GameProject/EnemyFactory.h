#pragma once
#ifndef _ENEMYFACTORY_H_
#define _ENEMYFACTORY_H_

#include "Component.h"

class PrefabAsset;

class EnemyFactory : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(EnemyFactory,Component)

private:
	void Update();
	void Load(json::JSON& jsonData) override;

	void CreateEnemy();

private:
	float createTimer = 0.0f;
	PrefabAsset* enemyPrefab;
};

#endif


