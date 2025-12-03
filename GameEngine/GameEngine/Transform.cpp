#include "EngineCore.h"
#include "Transform.h"

IMPLEMENT_DYNAMIC_CLASS(Transform);

const glm::mat3& Transform::GetMatrix() const
{
	if (isDirty)
	{
		float c = cos(rotation);
		float s = sin(rotation);

		cachedMatrix = glm::mat3(
			c * scale.x, s * scale.x, 0.0f,
			-s * scale.y, c * scale.y, 0.0f,
			position.x, position.y, 1.0f
		);
		isDirty = false;
	}
	return cachedMatrix;
}

void Transform::Load(json::JSON& data)
{
	Component::Load(data);
	if (data.hasKey("position"))
	{
		auto posJson = data.at("position");
		position.x = static_cast<float>(posJson.at("x").ToFloat());
		position.y = static_cast<float>(posJson.at("y").ToFloat());
	}
	if (data.hasKey("scale"))
	{
		auto scaleJson = data.at("scale");
		scale.x = static_cast<float>(scaleJson.at("x").ToFloat());
		scale.y = static_cast<float>(scaleJson.at("y").ToFloat());
	}
	if (data.hasKey("rotation"))
	{
		rotation = static_cast<float>(data.at("rotation").ToFloat());
	}
}