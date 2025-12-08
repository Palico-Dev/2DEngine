#include "GameCore.h"
#include "Meteor.h"
#include "FileManager.h"

IMPLEMENT_DYNAMIC_CLASS(Meteor)
CLONEABLE_IMPLEMENT(Meteor)


void Meteor::Start()
{
	health = maxHealth;
}

void Meteor::Load(json::JSON& jsonData)
{
	maxHealth = FileManager::JsonReadInt(jsonData, "health");
}

void Meteor::GetDamage()
{
	health--;
	if (health <= 0)
		Gameplay::Destroy(owner);
}
