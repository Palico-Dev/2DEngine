#include "GameCore.h"
#include "Background.h"
#include "FileManager.h"
#include "AssetManager.h"
#include "PrefabAsset.h"
#include "Random.h"
#include "Entity.h"
#include "BackgroundItem.h"
#include "GameController.h"

IMPLEMENT_DYNAMIC_CLASS(Background)

void Background::Update()
{
	if (!GameController::Instance().isGameStarted)
		return;

	Time& time = Time::Instance();

	starTimer -= time.DeltaTime();
	speedlineTimer -= time.DeltaTime();
	nebulaTimer -= time.DeltaTime();

	if (starTimer <= 0)
	{
		CreateStar();
		starTimer = Random::Float(1.0f, 2.0f);
	}
	if (speedlineTimer <= 0)
	{
		CreateSpeedline();
		speedlineTimer = Random::Float(3.0f, 5.0f);
	}
	if (nebulaTimer <= 0)
	{
		CreateNebula();
		nebulaTimer = Random::Float(5.0f, 7.0f);
	}

}

void Background::Load(json::JSON& jsonData)
{
	starSmallName = FileManager::JsonReadString(jsonData, "starSmall");
	starBigName = FileManager::JsonReadString(jsonData, "starBig");
	nebulaName = FileManager::JsonReadString(jsonData, "nebula");
	speedlineName = FileManager::JsonReadString(jsonData, "speedline");

	starSmall = AssetManager::Instance().GetAsset<PrefabAsset>(starSmallName);
	starBig = AssetManager::Instance().GetAsset<PrefabAsset>(starBigName);
	nebula = AssetManager::Instance().GetAsset<PrefabAsset>(nebulaName);
	speedline = AssetManager::Instance().GetAsset<PrefabAsset>(speedlineName);
}

void Background::CreateNebula()
{
	Entity* e = Gameplay::Spawn(nebula, { Random::Float(150.0f,600.0f),-100 });
}

void Background::CreateSpeedline()
{
	Entity* e = Gameplay::Spawn(speedline, { Random::Float(10.0f,740.0f),-100 });
}

void Background::CreateStar()
{
	if (Random::Bool())
	{
		Entity* e = Gameplay::Spawn(starBig, { Random::Float(10.0f,740.0f),-100 });
	}
	else
	{
		Entity* e = Gameplay::Spawn(starSmall, { Random::Float(10.0f,740.0f),-100 });
	}

}
