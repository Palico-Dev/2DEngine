#include "GameCore.h"
#include "Meteor.h"
#include "FileManager.h"
#include "Entity.h"
#include "Transform.h"
#include "Collider.h"

IMPLEMENT_DYNAMIC_CLASS(Meteor)
CLONEABLE_IMPLEMENT(Meteor)


void Meteor::Start()
{
	health = maxHealth;
}

void Meteor::Load(json::JSON& jsonData)
{
	maxHealth = FileManager::JsonReadInt(jsonData, "health");
	speed = FileManager::JsonReadFloat(jsonData, "speed");
}

void Meteor::Update()
{
	owner->transform->Translate(dir * speed * Time::Instance().DeltaTime());
}

void Meteor::GetDamage()
{
	health--;
	if (health <= 0)
		Gameplay::Destroy(owner);
}

void Meteor::OnTriggerEnter(Collider* other)
{
	if (other->owner->HasTag("Enemy"))
	{
		other->owner->GetComponent<>()
	}
}
