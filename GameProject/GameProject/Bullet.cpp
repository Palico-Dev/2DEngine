#include "GameCore.h"
#include "Bullet.h"
#include "FileManager.h"
#include "Entity.h"
#include "Transform.h"

IMPLEMENT_DYNAMIC_CLASS(Bullet);

void Bullet::Update()
{
	if (owner->transform->GetPosition().y < 0)
	{
		Gameplay::Destroy(owner);
	}
	owner->transform->SetPosition(owner->transform->GetPosition() + dir * speed * Time::Instance().DeltaTime());
}

void Bullet::Start()
{

}

void Bullet::Initialize()
{

}

Component* Bullet::Clone()
{
	Bullet* clone = (Bullet*)CreateObject("Bullet");

	*clone = *this;

	clone->owner = nullptr;
	return clone;
}

void Bullet::Load(json::JSON& jsonData)
{
	Component::Load(jsonData);

	speed = FileManager::JsonReadFloat(jsonData, "speed");
	dir = FileManager::JsonReadVec2(jsonData, "direction");
}
