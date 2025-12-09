#include "GameCore.h"
#include "Bullet.h"
#include "FileManager.h"
#include "Entity.h"
#include "Transform.h"
#include "Collider.h"
#include "Meteor.h"
#include "Enemy.h"
#include "PlayerController.h"

IMPLEMENT_DYNAMIC_CLASS(Bullet);
CLONEABLE_IMPLEMENT(Bullet)

void Bullet::Update()
{
	if (owner->transform->GetPosition().y < -10.0f || owner->transform->GetPosition().y > 1050.0f || owner->transform->GetPosition().x > 770.0f || owner->transform->GetPosition().x < -10.0f)
	{
		Gameplay::Destroy(owner);
	}
	owner->transform->Translate(dir * speed * Time::Instance().DeltaTime());
}

void Bullet::Start()
{

}

void Bullet::Load(json::JSON& jsonData)
{
	Component::Load(jsonData);

	speed = FileManager::JsonReadFloat(jsonData, "speed");
	dir = FileManager::JsonReadVec2(jsonData, "direction");

	auto jsonNode = FileManager::JsonReadArray(jsonData, "targetTags");
	for (auto& n : jsonNode)
	{
		targetTags.push_back(n.ToString());
	}
}

void Bullet::SetDirection(glm::vec2 newDir)
{
	dir = newDir;
	owner->transform->LookAt({ -newDir.y,newDir.x });
}

void Bullet::OnTriggerEnter(Collider* other)
{
	if (other->owner->HasTag("Meteor") && Utility::VectorContains<std::string>(targetTags, "Meteor"))
	{
		other->owner->GetComponent<Meteor>()->GetDamage();
		Gameplay::Destroy(owner);
	}
	if (other->owner->HasTag("Enemy") && Utility::VectorContains<std::string>(targetTags, "Enemy"))
	{
		other->owner->GetComponent<Enemy>()->GetDamage();
		Gameplay::Destroy(owner);
	}
	if (other->owner->HasTag("Player") && Utility::VectorContains<std::string>(targetTags, "Player"))
	{
		other->owner->GetComponent<PlayerController>()->GetDamage();
		Gameplay::Destroy(owner);
	}

}
