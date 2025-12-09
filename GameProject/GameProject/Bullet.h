#pragma once
#ifndef _BULLET_H_
#define _BULLET_H_

#include "Component.h"

class Collider;

class Bullet : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Bullet, Component);
	CLONEABLE(Bullet)
public:
	void Update() override;
	void Start() override;
	void Load(json::JSON& jsonData) override;

public:
	void SetDirection(glm::vec2 newDir);

protected:
	void OnTriggerEnter(Collider* other) override;

private:
	float speed = 0.0f;
	glm::vec2 dir = { 0,0 };

private:
	std::vector<std::string> targetTags;
};

#endif


