#pragma once

#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "Object.h"
enum class ComponentLifeState {
	Uninitialized,
	Alive,
	PendingDestroy,
	Destroyed
};

class Entity;
class Transform;
class Component : public Object
{
	DECLARE_ABSTRACT_DERIVED_CLASS(Component, Object)
private:
	Entity* owner = nullptr;
	ComponentLifeState lifeState = ComponentLifeState::Uninitialized;
	friend class Entity;

public:
	/// <summary>
	/// Initialize the Component.
	/// </summary>
	void Initialize() override;

	/// <summary>
	/// Get the current life state of this Component.
	/// </summary>
	/// <returns></returns>
	ComponentLifeState GetLifeState() const { return lifeState; }

	/// <summary>
	/// Load Component data from JSON.
	/// </summary>
	/// <param name="jsonData"></param>
	void Load(json::JSON& jsonData) override;

	/// <summary>
	/// Handy method to get the Transform Component from the owning Entity.
	/// </summary>
	/// <returns></returns>
	Transform* GetTransform() const;

	/// <summary>
	/// Get the Entity that owns this Component.
	/// </summary>
	/// <returns></returns>
	Entity* GetOwner() const { return owner; }

protected:
	void Destroy() override;

	/// <summary>
	/// Marks the component for destruction by setting its lifeState to ComponentLifeState::PendingDestroy.
	/// </summary>
	void MarkForDestroy() { lifeState = ComponentLifeState::PendingDestroy; }

	/// <summary>
	/// Update the Component.
	/// Implement component specific update logic in derived classes.
	/// </summary>
	virtual void Update() {};

	/// <summary>
	/// For derived classes to implement custom logic upon initialization.
	/// </summary>
	virtual void OnComponentInitialized() {};	
};

#endif	// _COMPONENT_H_
