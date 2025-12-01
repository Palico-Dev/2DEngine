#pragma once
#include "Component.h"

class Transform : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Transform, Component);

public:
	// virtual ~Transform() = default;
	
	const glm::mat4& GetMatrix() const {
		if (isDirty) {
			cachedMatrix = 
				glm::translate(glm::mat4(1.0f), glm::vec3(position, zIndex)) *
				glm::rotate(glm::mat4(1.0f), rotation, glm::vec3(0.0f, 0.0f, 1.0f)) *
				glm::scale(glm::mat4(1.0f), glm::vec3(scale, 1.0f));

			isDirty = false;
		}
		return cachedMatrix;
	}

	void SetPosition(const glm::vec2& pos) {
		position = pos;
		isDirty = true;
	}
	glm::vec2 GetPosition() const {
		return position;
	}

	void SetScale(const glm::vec2& scl) {
		scale = scl;
		isDirty = true;
	}
	glm::vec2 GetScale() const {
		return scale;
	}

	void SetRotation(float rotRadians) {
		rotation = rotRadians;
		isDirty = true;
	}
	float GetRotation() const {
		return rotation;
	}

	void SetRotationDegrees(float rotDegrees) {
		SetRotation(glm::radians(rotDegrees));
	}

	float GetRotationDegrees() const {
		return glm::degrees(rotation);
	}

	void SetZIndex(float z) {
		zIndex = z;
		isDirty = true;
	}

	float GetZIndex() const {
		return zIndex;
	}

	void Load(json::JSON& data);
private:
	glm::vec2 position = glm::vec2(0.0f, 0.0f);
	glm::vec2 scale = glm::vec2(1.0f, 1.0f);
	float rotation = 0.0f; // In radians
	float zIndex = 0.0f;

	mutable bool isDirty = true;
	mutable glm::mat4 cachedMatrix = glm::mat4(1.0f);
};

