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

void Entity::Start()
{
	for (auto& component : components)
	{
		component->Start();
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

bool Entity::HasTag(const std::string& tag)
{
	STRCODE hashcode = GetHashCode(tag.c_str());
	for (auto& t : tags)
	{
		if (t == hashcode)
			return true;
	}
	return false;
}

void Entity::Load(json::JSON& jsonData)
{
	Object::Load(jsonData);

	name = FileManager::JsonReadString(jsonData, "name");

	auto tagNodes = FileManager::JsonReadArray(jsonData, "tags");
	for (auto& tagJson : tagNodes)
	{
		tags.push_back(GetHashCode(tagJson.ToString().c_str()));
	}

	json::JSON componentsJson = jsonData.at("components");
	for (auto& comp : componentsJson.ArrayRange()) {
		std::string compType = FileManager::JsonReadString(comp,"type");
		Component* component = CreateComponent(compType);
		component->Load(comp);
	}
}

Entity* Entity::Clone()
{
	Entity* cloneEntity = (Entity*)CreateObject("Entity");
	for (auto& c : components)
	{
		Component* cloneComponent = c->Clone();
		cloneEntity->components.push_back(cloneComponent);
		cloneComponent->owner = cloneEntity;
		if (cloneComponent->GetDerivedTypeClassHashCode() == Transform::GetTypeClassHashCode())
		{
			cloneEntity->transform = (Transform*)cloneComponent;
		}
	}
	cloneEntity->tags = tags;
	cloneEntity->name = name;
	return cloneEntity;

}
