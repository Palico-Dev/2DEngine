#include "EngineCore.h"
#include "Entity.h"
#include "Component.h"
#include "Transform.h"
#include "FileManager.h"

IMPLEMENT_DYNAMIC_CLASS(Entity)

void Entity::Initialize()
{
	if (initialized)
		return;
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
		component->Update();
	}
}

Component* Entity::CreateComponent(const std::string& componentType)
{
	if(componentType == "Transform" && transform != nullptr)
	{
		return nullptr;
	}

	Component* component = (Component*)CreateObject(componentType.c_str());
	if (component)
	{
		component->owner = this;
		components.push_back(component);
		if (componentType == "Transform")
		{
			transform = (Transform*)component;
		}
		
		return component;
	}
	return nullptr;
}

bool Entity::RemoveComponent(Component* component)
{
	//if(component == nullptr || component == transform)
	//{
		return false;
	//}

	//component->MarkForDestroy();
	//return true;
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

Component* const Entity::GetComponentByType(const std::string& comp_type)
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

std::vector<Component*> Entity::GetAllComponentsByType(const std::string& comp_type)
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
		std::string compType = FileManager::JsonReadString(comp,"type");
		Component* component = CreateComponent(compType);
		component->Load(comp);
	}
}