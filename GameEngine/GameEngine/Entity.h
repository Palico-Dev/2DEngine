#pragma once

#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "Object.h"


enum class EntityLifeState {
	Alive,
	PendingDestroy,
	Destroyed
};
class Scene;
class Component;
class Transform;

class Entity final : public Object
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Entity, Object)
private:
	std::list<Component*> components;
	Transform* transform = nullptr;
	EntityLifeState lifeState = EntityLifeState::Alive;
	friend class Scene;

private:
	/// <summary>
	/// Entity should be deleted only by Scene and itself.
	/// </summary>
	void Destroy() override;

	
public:
	/// <summary>
	/// Initialize the Entity and its Components.
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// Update all Components attached to this Entity.
	/// As well as perform Entity specific update logic. e.g.(delete)
	/// 
	/// </summary>
	void Update();

	/// <summary>
	///	Delete this Entity at the end of the current frame.
	/// </summary>
	void MarkForDestroy() { lifeState = EntityLifeState::PendingDestroy; }

	/// <summary>
	/// Create a Component of the given type and attach it to this Entity.
	/// </summary>
	/// <param name="componentType"></param>
	/// <returns></returns>
	Component* CreateComponent(const std::string& componentType);

	/// <summary>
	///	Detach the given Component from this Entity and mark it for deletion.
	/// </summary>
	/// <param name="component"></param>
	/// <returns></returns>
	bool RemoveComponent(Component* component);

	/// <summary>
	/// Get the current life state of this Entity.
	/// </summary>
	/// <returns></returns>
	EntityLifeState GetLifeState() const { return lifeState; }

	/// <summary>
	/// Find the first Component attached to this Entity by its type name.
	/// </summary>
	/// <param name="comp_type"></param>
	/// <returns></returns>
	Component* const FindFirstComponentByType(const std::string& comp_type);

	/// <summary>
	/// Find all Components attached to this Entity by its type name.
	/// </summary>
	/// <param name="comp_type"></param>
	/// <returns></returns>
	std::vector<Component*> FindComponentsByType(const std::string& comp_type);

	/// <summary>
	/// Load Entity data from JSON.
	/// </summary>
	/// <param name="jsonData"></param>
	void Load(json::JSON& jsonData) override;

	/// <summary>
	/// Get the Transform Component attached to this Entity.
	/// One Transform is guaranteed to exist per Entity.
	/// </summary>
	/// <returns></returns>
	Transform* GetTransform() const { return transform; }
	
};

#endif	// _ENTITY_H_
