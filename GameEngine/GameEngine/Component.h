#pragma once

#ifndef _COMPONENT_H_
#define _COMPONENT_H_

#include "Object.h"

class Entity;
class Transform;
class Component : public Object
{
	DECLARE_ABSTRACT_DERIVED_CLASS(Component, Object)

public:
	void Initialize() override;
	void Load(json::JSON& jsonData) override;
	virtual Component* Clone() = 0;

public:
	Entity* owner = nullptr;

protected:
	void Destroy() override;
	virtual void Update() {};
	virtual void Start() {};

private:

	friend class Entity;
};

#endif	// _COMPONENT_H_
