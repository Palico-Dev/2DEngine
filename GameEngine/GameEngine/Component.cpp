#include "EngineCore.h"
#include "Component.h"
#include "Entity.h"

IMPLEMENT_ABSTRACT_CLASS(Component)

void Component::Initialize()
{
	if(IsInitialized())
		return;

	// 1. Call base class Initialize
	Object::Initialize();
	SetInitialized(true);

	// 2. Set life state to Alive
	lifeState = ComponentLifeState::Alive;

	// 3. Call derived class OnComponent
	OnComponentInitialized();
}

void Component::Destroy()
{
	Object::Destroy();
}

void Component::Load(json::JSON& jsonData)
{
	Object::Load(jsonData);
} 

Transform* Component::GetTransform() const
{
	if (owner) {
		return owner->GetTransform();
	}
	return nullptr;
};