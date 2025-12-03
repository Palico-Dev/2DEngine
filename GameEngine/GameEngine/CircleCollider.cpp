#include "EngineCore.h"
#include "CircleCollider.h"

IMPLEMENT_DYNAMIC_CLASS(CircleCollider);

float CircleCollider::GetRadiusWorld() const
{
#if COLLISIONTEST
	return radius;
#endif
	glm::vec2 s = owner->transform->GetScale();
	float uniformScale = std::max(s.x, s.y);
	return radius * uniformScale;
}

AABB CircleCollider::GetAABB()
{
	glm::vec2 center = GetCenterWorld();
	float r = GetRadiusWorld();

	return {
		center - glm::vec2(r, r),
		center + glm::vec2(r, r)
	};
}

void CircleCollider::Initialize()
{
	Collider::Initialize();
}

void CircleCollider::Destroy()
{
	Collider::Destroy();
}

void CircleCollider::Load(json::JSON& _jsonData)
{
	Collider::Load(_jsonData);

    if (_jsonData.hasKey("radius"))
    {
        radius = _jsonData["radius"].ToFloat();
    }
}