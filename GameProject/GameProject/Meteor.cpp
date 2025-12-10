#include "GameCore.h"
#include "Meteor.h"
#include "FileManager.h"
#include "Entity.h"
#include "Transform.h"
#include "Collider.h"
#include "Enemy.h"
#include "PlayerController.h"
#include "Random.h"
#include "GameController.h"

IMPLEMENT_DYNAMIC_CLASS(Meteor)
CLONEABLE_IMPLEMENT(Meteor)


void Meteor::Start()
{
	health = maxHealth;
}

void Meteor::Load(json::JSON& jsonData)
{
	maxHealth = FileManager::JsonReadInt(jsonData, "health");
	aSpeed = FileManager::JsonReadFloat(jsonData, "speed");
	speed = Random::Float(aSpeed - 20.0f, aSpeed + 20.0f);
}

void Meteor::Serialize(json::JSON& j)
{
	FileManager::JsonWriteInt(j, "health", maxHealth);
	FileManager::JsonWriteFloat(j, "speed", speed);
}

void Meteor::Deserialize(json::JSON& j)
{
	maxHealth = FileManager::JsonReadInt(j, "health");
	speed = FileManager::JsonReadFloat(j,"speed");
}

void Meteor::Update()
{
	owner->transform->Translate(dir * speed * Time::Instance().DeltaTime());
	if (owner->transform->GetPosition().y > 1100.0f)
		Gameplay::Destroy(owner);
}

void Meteor::GetDamage()
{
	health--;
	if (health <= 0)
	{
		Gameplay::Destroy(owner);
		GameController::Instance().AddScore(15);
	}

}

void Meteor::OnTriggerEnter(Collider* other)
{
	if (other->owner->HasTag("Enemy"))
	{
		other->owner->GetComponent<Enemy>()->GetDamage();
		Gameplay::Destroy(owner);
	}
	if (other->owner->HasTag("Player"))
	{
		other->owner->GetComponent<PlayerController>()->GetDamage();
		Gameplay::Destroy(owner);
	}
}
