#include "GameCore.h"
#include "Enemy.h"
#include "FileManager.h"
#include "AssetManager.h"
#include "PrefabAsset.h"
#include "Transform.h"
#include "Entity.h"
#include "Collider.h"
#include "PlayerController.h"
#include "GameController.h"

IMPLEMENT_DYNAMIC_CLASS(Enemy)
CLONEABLE_IMPLEMENT(Enemy)

void Enemy::GetDamage()
{
	health--;
	if (health <= 0)
	{
		Gameplay::Destroy(owner);
		GameController::Instance().AddScore(25);
	}

}

void Enemy::Start()
{
	health = maxHealth;
}

void Enemy::Update()
{
	owner->transform->Translate(glm::vec2(0, 1) * speed * Time::Instance().DeltaTime());
	if (owner->transform->GetPosition().y > 1050.0f)
	{
		Gameplay::Destroy(owner);
	}

	shootTimer -= Time::Instance().DeltaTime();
	if (shootTimer <= 0)
	{
		Shoot();
		shootTimer = shootInterval;
	}

}

void Enemy::Load(json::JSON& jsonData)
{
	maxHealth = FileManager::JsonReadInt(jsonData, "health");
	shootInterval = FileManager::JsonReadFloat(jsonData, "shootInterval");
	bullet = AssetManager::Instance().GetAsset<PrefabAsset>(FileManager::JsonReadString(jsonData, "bullet"));
}

void Enemy::Shoot()
{
	Gameplay::Spawn(bullet, owner->transform->GetPosition() + glm::vec2(0, 20));
}

void Enemy::OnTriggerEnter(Collider* other)
{
	if (other->owner->HasTag("Player"))
	{
		other->owner->GetComponent<PlayerController>()->GetDamage();
		Gameplay::Destroy(owner);
	}
}
