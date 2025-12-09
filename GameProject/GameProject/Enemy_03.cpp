#include "GameCore.h"
#include "Enemy_03.h"
#include "FileManager.h"
#include "AssetManager.h"
#include "PrefabAsset.h"
#include "Transform.h"
#include "Entity.h"
#include "Collider.h"
#include "PlayerController.h"
#include "GameController.h"
#include "Bullet.h"

IMPLEMENT_DYNAMIC_CLASS(Enemy_03)
CLONEABLE_IMPLEMENT(Enemy_03)

void Enemy_03::Start()
{
	Enemy::Start();
}

void Enemy_03::Update()
{
	owner->transform->Translate(glm::vec2(1, 0) * speed * Time::Instance().DeltaTime());
	owner->transform->Rotate(speed * Time::Instance().DeltaTime());
	if (owner->transform->GetPosition().x > 770.0f)
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

void Enemy_03::Load(json::JSON& jsonData)
{
	Enemy::Load(jsonData);
}

void Enemy_03::Shoot()
{
	auto b1 = Gameplay::Spawn(bullet, owner->transform->GetPosition());
	b1->GetComponent<Bullet>()->SetDirection(-owner->transform->GetRight());
	auto b2 = Gameplay::Spawn(bullet, owner->transform->GetPosition());
	b2->GetComponent<Bullet>()->SetDirection(owner->transform->GetRight());
	auto b3 = Gameplay::Spawn(bullet, owner->transform->GetPosition());
	b3->GetComponent<Bullet>()->SetDirection(owner->transform->GetForward());
	auto b4 = Gameplay::Spawn(bullet, owner->transform->GetPosition());
	b4->GetComponent<Bullet>()->SetDirection(-owner->transform->GetForward());
}

void Enemy_03::OnTriggerEnter(Collider* other)
{
	Enemy::OnTriggerEnter(other);
}
