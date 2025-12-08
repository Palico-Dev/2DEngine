#include "GameCore.h"
#include "EnemyFactory.h"
#include "FileManager.h"
#include "AssetManager.h"
#include "Random.h"

IMPLEMENT_DYNAMIC_CLASS(EnemyFactory)

void EnemyFactory::Update()
{
	createTimer -= Time::Instance().DeltaTime();
	if (createTimer <= 0)
	{
		CreateEnemy();
		createTimer = Random::Float(3.0f, 5.0f);
	}
}

void EnemyFactory::Load(json::JSON& jsonData)
{
	enemyPrefab = AssetManager::Instance().GetAsset<PrefabAsset>(FileManager::JsonReadString(jsonData, "enemy"));

}

void EnemyFactory::CreateEnemy()
{
	Gameplay::Spawn(enemyPrefab, { Random::Float(50.0f,700.0f),0 });
}
