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
	auto jsonNodes = FileManager::JsonReadArray(jsonData, "enemy");
	for (auto& j : jsonNodes)
	{
		PrefabAsset* p = AssetManager::Instance().GetAsset<PrefabAsset>(j.ToString());
		enemyPrefabs.push_back(p);
	}

}

void EnemyFactory::CreateEnemy()
{
	int index = Random::Int(0, 2);
	if (index == 2)
	{
		Gameplay::Spawn(enemyPrefabs[index], { 0,Random::Float(50.0f,700.0f) });
	}
	else
	{
		Gameplay::Spawn(enemyPrefabs[index], {Random::Float(50.0f,700.0f),0});
	}

}
