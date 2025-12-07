#pragma once
#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "Component.h"

class Transform : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Transform, Component);

public:
	const glm::mat3& GetMatrix() const;

	void SetPosition(const glm::vec2& pos)
	{
		position = pos;
		isDirty = true;
	}
	glm::vec2 GetPosition() const { return position; }

	void SetScale(const glm::vec2& scl)
	{
		scale = scl;
		isDirty = true;
	}
	glm::vec2 GetScale() const { return scale; }

	void SetRotation(float rotRadians)
	{
		rotation = rotRadians;
		isDirty = true;
	}
	float GetRotation() const { return rotation; }

	void SetRotationDegrees(float rotDegrees)
	{
		SetRotation(glm::radians(rotDegrees));
	}
	float GetRotationDegrees() const
	{
		return glm::degrees(rotation);
	}

	void SetZIndex(float z)
	{
		zIndex = z;
	}
	float GetZIndex() const { return zIndex; }

	void Load(json::JSON& data);
	Component* Clone() override;

private:
	glm::vec2 position = glm::vec2(0.0f, 0.0f);
	glm::vec2 scale = glm::vec2(1.0f, 1.0f);
	float rotation = 0.0f; 
	float zIndex = 0.0f;

	mutable bool isDirty = true;
	mutable glm::mat3 cachedMatrix = glm::mat3(1.0f);
};
#endif