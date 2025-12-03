#include "GameCore.h"
#include "NextLevel.h"
#include "Entity.h"
#include "SceneManager.h"

IMPLEMENT_DYNAMIC_CLASS(NextLevel)

void NextLevel::Initialize()
{
	Component::Initialize();
}

void NextLevel::OnTriggerEnter(Collider* other)
{
	std::cout << "Enter" << std::endl;
	//SceneManager::Instance().QueueActiveScene("Level2");
}

void NextLevel::OnComponentInitialized()
{
	Collider* collider = (Collider*)GetOwner()->FindFirstComponentByType("CircleCollider");
	if (collider == nullptr)
	{
		std::cout << "Cannot find Collider" << std::endl;
		return;
	}
	collider->onEnter = [this](Collider* other) {
		this->OnTriggerEnter(other);
		};
}
