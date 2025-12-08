#include "GameCore.h"
#include "Bullet.h"
#include "FileManager.h"
#include "Entity.h"
#include "Transform.h"
#include "Collider.h"
#include "Meteor.h"

IMPLEMENT_DYNAMIC_CLASS(Bullet);
CLONEABLE_IMPLEMENT(Bullet)

void Bullet::Update()
{
	if (owner->transform->GetPosition().y < 0)
	{
		Gameplay::Destroy(owner);
	}
	owner->transform->Translate(dir * speed * Time::Instance().DeltaTime());
}

void Bullet::Start()
{
	Debug::Log("Bullet Start");

	Collider* collider = owner->GetComponent<Collider>();
	if (collider == nullptr)
	{
		std::cout << "Cannot find Collider" << std::endl;
		return;
	}
	collider->onEnter = [this](Collider* other) {
		this->OnTriggerEnter(other);
		};
}

void Bullet::Load(json::JSON& jsonData)
{
	Component::Load(jsonData);

	speed = FileManager::JsonReadFloat(jsonData, "speed");
	dir = FileManager::JsonReadVec2(jsonData, "direction");
}

void Bullet::OnTriggerEnter(Collider* other)
{
	Debug::Log(other->owner->name);
	if (other->owner->HasTag("Meteor"))
	{
		other->owner->GetComponent<Meteor>()->GetDamage();
		Gameplay::Destroy(owner);
	}

}
