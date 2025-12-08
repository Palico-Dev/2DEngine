#pragma once
#ifndef _METEOR_H_
#define _METEOR_H_

#include "Component.h"

class Meteor : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Meteor, Component);
	CLONEABLE(Meteor)
public:
	void Start() override;
	void Load(json::JSON& jsonData) override;
	void Update();

	void GetDamage();
	void OnTriggerEnter(Collider* other);
private:
	int maxHealth = 3;
	int health = maxHealth;

	float speed = 100.0f;
	glm::vec2 dir = { 0,1 };
};

#endif


