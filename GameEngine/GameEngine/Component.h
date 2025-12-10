#pragma once

#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "Object.h"

class Entity;
class Transform;
class Collider;
class Component : public Object
{
	DECLARE_ABSTRACT_DERIVED_CLASS(Component, Object)

public:
	void Initialize() override;
	void Load(json::JSON& jsonData) override;
	virtual Component* Clone() { return nullptr; };

	virtual void Serialize(json::JSON& j){}
	virtual void Deserialize(json::JSON& j){}


public:
	Entity* owner = nullptr;

protected:
	void Destroy() override;
	virtual void Update() {};
	virtual void Start() {};

	virtual void OnCollisionEnter(Collider* other) {}
	virtual void OnCollisionStay(Collider* other) {}
	virtual void OnCollisionExit(Collider* other) {}

	virtual void OnTriggerEnter(Collider* other) {}
	virtual void OnTriggerStay(Collider* other) {}
	virtual void OnTriggerExit(Collider* other) {}

private:

	friend class Entity;
};

#endif	// _COMPONENT_H_
