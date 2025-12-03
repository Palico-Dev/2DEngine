#include "EngineCore.h"
#include "Component.h"
#include "Entity.h"

IMPLEMENT_ABSTRACT_CLASS(Component)

void Component::Initialize()
{
	if(initialized)
		return;

	Object::Initialize();

}

void Component::Destroy()
{
	Object::Destroy();
}

void Component::Load(json::JSON& jsonData)
{
	Object::Load(jsonData);
} 