#pragma once
#ifndef _BOXCOLLIDER_H_
#define _BOXCOLLIDER_H_
#include "Collider.h"
#include "CollisionMath.h"
#include "Entity.h"


class BoxCollider:public Collider
{
	DECLARE_DYNAMIC_DERIVED_CLASS(BoxCollider, Collider);

public:
	ColliderType GetType() const override { return ColliderType::Box; }
	void SetSize(glm::vec2 newSize) { size = newSize; }
	glm::vec2 GetSize() const { return size; }

	AABB GetAABB() override;
	std::vector<glm::vec2> GetVertices(bool force = false);

	void Initialize() override;
	void Destroy() override;

	void Load(json::JSON& _jsonData) override;
	Component* Clone() override;

private:
	std::vector<glm::vec2> vertices;
	glm::vec2 size = { 1.0f, 1.0f };

private:
	//void Render() override;
	
#if COLLISIONTEST
public:
	void SetVertices(std::vector<glm::vec2> v) { vertices = v; }
#endif
};



#endif

