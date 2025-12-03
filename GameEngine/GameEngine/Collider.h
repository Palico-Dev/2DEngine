#pragma once
#ifndef _COLLIDER_H_
#define _COLLIDER_H_

#include "Component.h"
#include "CollisionSystem.h"
#include "CollisionMath.h"
#include "Renderable.h"
#include "Transform.h"

class Collider : public Renderable
{
	DECLARE_ABSTRACT_DERIVED_CLASS(Collider,Component);

public:
	void Initialize() override;
	void Destroy() override;

	virtual ColliderType GetType() const = 0;

	virtual glm::vec2 GetCenter() const { return center; }
	virtual glm::vec2 GetCenterWorld() const;

	void SetCenter(glm::vec2 newCenter) { center = newCenter; }

	virtual AABB GetAABB() = 0;

public:
	bool isTrigger = false;
	bool isRendered = false;
	int layer = 0;
	bool isStatic = false;
	float mass = 1.0f;

	//On collision event callbacks
	std::function<void(Collider*)> onEnter;
	std::function<void(Collider*)> onStay;
	std::function<void(Collider*)> onExit;

	virtual void Load(json::JSON& _jsonData) override;

protected:
	void Render() override;
protected:
	glm::vec2 center = { 0,0 };

	glm::vec2 lastPosition = { 0, 0 };
	float lastRotation = 0.0f;
	glm::vec2 lastScale = { 1.0f, 1.0f };

	SDL_Texture* debugTexture = nullptr;


#if COLLISIONTEST
public:
	std::string name;

#endif
};
#endif
