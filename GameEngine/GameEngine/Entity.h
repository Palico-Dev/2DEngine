#pragma once

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Object.h"

class Scene;
class Component;
class Transform;

class Entity final : public Object
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Entity, Object)

public:
	void Initialize() override;
	void Update();

	Component* CreateComponent(const std::string& componentType);
	bool RemoveComponent(Component* component);

	Component* const GetComponentByType(const std::string& comp_type);
	std::vector<Component*> GetAllComponentsByType(const std::string& comp_type);

	template <typename T>
	T* GetComponent()
	{
		return (T*)GetComponentByType(T::GetTypeClassName());;
	}

	template <typename T>
	std::vector < T*> GetAllComponents()
	{
		std::vector<Component*> rawList = GetAllComponentsByType(T::GetTypeClassName());
		std::vector<T*> typedList;

		for (Component* c : rawList)
		{
			typedList.push_back((T*)c);
		}

		return typedList;
	}

	void Load(json::JSON& jsonData) override;

	Transform* transform = nullptr;

private:
	void Destroy() override;

private:
	std::list<Component*> components;

	friend class Scene;
};

#endif	// _ENTITY_H_
