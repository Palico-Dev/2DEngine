#include "EngineCore.h"
#include "Entity.h"
#include "Component.h"
#include "Transform.h"

IMPLEMENT_DYNAMIC_CLASS(Entity)

void Entity::Initialize()
{
	Object::Initialize();

	for (auto& component : components)
	{
		component->Initialize();
	}
}

void Entity::Update()
{
	for (auto& component : components)
	{
		if (component->GetLifeState() != ComponentLifeState::Alive) continue;
		component->Update();
	}

	// Deal with removals
	for(auto it = components.begin(); it != components.end(); )
	{
		Component* component = *it;
		if (component->GetLifeState() == ComponentLifeState::PendingDestroy ||
			component->GetLifeState() == ComponentLifeState::Destroyed)
		{
			component->Destroy();
			delete component;
			it = components.erase(it);
		}
		else
		{
			++it;
		}
	}
}

Component* Entity::CreateComponent(const std::string& componentType)
{
	if(componentType == "Transform" && transform != nullptr)
	{
		// Only one Transform allowed per Entity
		return nullptr;
	}

	Component* component = (Component*)CreateObject(componentType.c_str());
	if (component)
	{
		component->owner = this;
		components.push_back(component);
		if (componentType == "Transform")
		{
			transform = static_cast<Transform*>(component);
		}
		
		return component;
	}
	return nullptr;
}

bool Entity::RemoveComponent(Component* component)
{
	if(component == nullptr || component == transform)
	{
		return false;
	}

	component->MarkForDestroy();
	return true;
}

void Entity::Destroy()
{
	Object::Destroy();

	for (auto& component : components)
	{
		component->Destroy();
		delete component;
	}
	components.clear();
}

Component* const Entity::FindFirstComponentByType(const std::string& comp_type)
{
	for(auto component: components)
	{
		if (component->GetDerivedTypeClassName() == comp_type)
		{
			return component;
		}
	}
	return nullptr;
}

std::vector<Component*> Entity::FindComponentsByType(const std::string& comp_type)
{
	std::vector<Component*> result;
	result.reserve(components.size());

	for (auto* component : components)
	{
		if (component->GetDerivedTypeClassName() == comp_type)
		{
			result.push_back(component);
		}
	}
	return result;
}

void Entity::Load(json::JSON& jsonData)
{
	Object::Load(jsonData);

	json::JSON componentsJson = jsonData.at("components");
	for (auto& comp : componentsJson.ArrayRange()) {

		std::string compType = comp.at("type").ToString();
		Component* component = (Component*)CreateObject(compType.c_str());

		component->owner = this;
		component->Load(comp);
		components.push_back(component);

	}
}