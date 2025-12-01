#pragma once
#ifndef _CIRCLECOLLIDER_H_
#define _CIRCLECOLLIDER_H_
#include "Collider.h"
#include "CollisionMath.h"
#include "Entity.h"

class CircleCollider : public Collider
{
	DECLARE_DYNAMIC_DERIVED_CLASS(CircleCollider, Collider);

public:
    ColliderType GetType() const override { return ColliderType::Circle; }

    float GetRadius() const { return radius; }
    float GetRadiusWorld() const;
    void SetRadius(float r) { radius = r; }

    AABB GetAABB() override;

	void Initialize() override;
	void Destroy() override;

    void Load(json::JSON& _jsonData) override;

private:
	float radius = 1.0f;
};

#endif


