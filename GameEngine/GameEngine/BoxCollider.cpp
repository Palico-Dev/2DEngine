#include "EngineCore.h"
#include "BoxCollider.h"

IMPLEMENT_DYNAMIC_CLASS(BoxCollider);

AABB BoxCollider::GetAABB()
{
    auto verts = GetVertices();

    glm::vec2 min = verts[0];
    glm::vec2 max = verts[0];

    for (auto& v : verts)
    {
        if (v.x < min.x) min.x = v.x;
        if (v.y < min.y) min.y = v.y;
        if (v.x > max.x) max.x = v.x;
        if (v.y > max.y) max.y = v.y;
    }

    return { min, max };
}

std::vector<glm::vec2> BoxCollider::GetVertices(bool force)
{
#if COLLISIONTEST
	return vertices;
#endif
	//compares last frame transform with current
	if (force||(GetOwner()->GetTransform()->GetPosition() != lastPosition ||
		GetOwner()->GetTransform()->GetRotation() != lastRotation ||
		GetOwner()->GetTransform()->GetScale() != lastScale))
	{
		//updates if transforms are different
		lastPosition = GetOwner()->GetTransform()->GetPosition();
		lastRotation = GetOwner()->GetTransform()->GetRotation();
		lastScale = GetOwner()->GetTransform()->GetScale();

		//gather transformation info
		glm::vec2 pos = GetOwner()->GetTransform()->GetPosition();
		float rot = GetOwner()->GetTransform()->GetRotation();
		glm::vec2 scale = GetOwner()->GetTransform()->GetScale();

		//get the half-size
		glm::vec2 hs = (size * scale) * 0.5f;

		//define all 4 corners of box relative to center
		std::vector<glm::vec2> corners = { {-hs.x, -hs.y},
										  { hs.x, -hs.y},
										  { hs.x,  hs.y},
										  {-hs.x,  hs.y} };


		//rotate each corner around the origin and then translate to world position
		float c = cos(rot);
		float s = sin(rot);
		for (auto& point : corners)
		{
			glm::vec2 rotated{ point.x * c - point.y * s,
							   point.x * s + point.y * c };
			point = pos + rotated;
		}

		vertices = corners;
	}
	
	return vertices;
}

void BoxCollider::Initialize()
{
	Collider::Initialize();
	GetVertices(true);
}

void BoxCollider::Destroy()
{
	Collider::Destroy();
}

void BoxCollider::Load(json::JSON& _jsonData)
{
	Collider::Load(_jsonData);

	if (_jsonData.hasKey("size"))
	{
		auto s = _jsonData["size"];
		size.x = s["x"].ToFloat();
		size.y = s["y"].ToFloat();
	}
}
