#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

#include "Component.h"

class Bullet : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Bullet, Component);
public:
	void Update() override;
	void Start() override;
	Component* Clone() override;
	void Load(json::JSON& jsonData) override;

private:
	float speed = 0.0f;
	glm::vec2 dir = { 0,0 };
};

#endif


