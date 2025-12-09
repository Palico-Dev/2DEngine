#include "GameCore.h"
#include "Background.h"
#include "FileManager.h"
#include "AssetManager.h"
#include "PrefabAsset.h"
#include "Random.h"
#include "Entity.h"
#include "BackgroundItem.h"

IMPLEMENT_DYNAMIC_CLASS(Background)

void Background::Update()
{
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
	std::string n = FileManager::JsonReadString(jsonData, "backgroundItem");
	backgroundItem = AssetManager::Instance().GetAsset<PrefabAsset>(n);
}

void Background::CreateNebula()
{
	Entity* e = Gameplay::Spawn(backgroundItem, { Random::Float(150.0f,600.0f),-100 });
	e->GetComponent<BackgroundItem>()->Init(AssetManager::Instance().GetAsset<TextureAsset>("nebula.png"), { 241,168 }, 50.0f);
}

void Background::CreateSpeedline()
{
	Entity* e = Gameplay::Spawn(backgroundItem, { Random::Float(10.0f,740.0f),-100 });
	e->GetComponent<BackgroundItem>()->Init(AssetManager::Instance().GetAsset<TextureAsset>("speedLine.png"), { 7,186 }, 400.0f);
}

void Background::CreateStar()
{
	if (Random::Bool())
	{
		Entity* e = Gameplay::Spawn(backgroundItem, { Random::Float(10.0f,740.0f),-100 });
		e->GetComponent<BackgroundItem>()->Init(AssetManager::Instance().GetAsset<TextureAsset>("starBig.png"), { 23,21 }, Random::Float(50.0f,100.0f));
	}
	else
	{
		Entity* e = Gameplay::Spawn(backgroundItem, { Random::Float(10.0f,740.0f),-100 });
		e->GetComponent<BackgroundItem>()->Init(AssetManager::Instance().GetAsset<TextureAsset>("starSmall.png"), { 11,11 }, Random::Float(80.0f, 130.0f));
	}

}
