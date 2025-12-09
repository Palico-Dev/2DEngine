#include "GameCore.h"
#include "Enemy_02.h"
#include "FileManager.h"
#include "AssetManager.h"
#include "PrefabAsset.h"
#include "Transform.h"
#include "Entity.h"
#include "Collider.h"
#include "PlayerController.h"
#include "GameController.h"

IMPLEMENT_DYNAMIC_CLASS(Enemy_02)
CLONEABLE_IMPLEMENT(Enemy_02)


void Enemy_02::Start()
{
	Enemy::Start();
}

void Enemy_02::Update()
{
	owner->transform->Translate(glm::vec2(moveRight, 0) * speed * Time::Instance().DeltaTime());
	if (owner->transform->GetPosition().x > 730 || owner->transform->GetPosition().x < 30)
		moveRight = -moveRight;

	Enemy::Update();

}

void Enemy_02::Load(json::JSON& jsonData)
{
	Enemy::Load(jsonData);
}


void Enemy_02::OnTriggerEnter(Collider* other)
{
	Enemy::OnTriggerEnter(other);
}
