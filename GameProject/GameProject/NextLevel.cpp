#include "GameCore.h"
#include "NextLevel.h"
#include "Entity.h"
#include "SceneManager.h"

IMPLEMENT_DYNAMIC_CLASS(NextLevel)

void NextLevel::Initialize()
{
	if (initialized)
		return;
	Component::Initialize();

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

void NextLevel::OnTriggerEnter(Collider* other)
{
	std::cout << "Enter" << std::endl;
	//SceneManager::Instance().QueueActiveScene("Level2");
}
