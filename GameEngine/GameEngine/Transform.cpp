#include "EngineCore.h"
#include "Transform.h"
#include "FileManager.h"

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

void Transform::Translate(glm::vec2 dir)
{
	SetPosition(GetPosition() + dir);
}

void Transform::Rotate(float angle)
{
	SetRotationDegrees(GetRotationDegrees() + angle);
}

void Transform::LookAt(const glm::vec2& direction)
{
	if (glm::length(direction) < 0.001f)
	{
		return;
	}
	float angleRadians = glm::atan(direction.y, direction.x);

	SetRotation(angleRadians);
}

void Transform::Load(json::JSON& data)
{
	Component::Load(data);
	position = FileManager::JsonReadVec2(data, "position");
	scale = FileManager::JsonReadVec2(data, "scale");
	rotation = FileManager::JsonReadFloat(data, "rotation");
}

Component* Transform::Clone()
{
	Transform* clone = (Transform*)CreateObject("Transform");

	*clone = *this;

	clone->owner = nullptr;
	return clone;
}

void Transform::Serialize(json::JSON& j)
{
	FileManager::JsonWriteVec2(j, "position", position);
	FileManager::JsonWriteVec2(j, "scale", scale);
	FileManager::JsonWriteFloat(j, "rotation", rotation);
}

void Transform::Deserialize(json::JSON& j)
{
	position = FileManager::JsonReadVec2(j, "position");
	scale = FileManager::JsonReadVec2(j, "scale");
	rotation = FileManager::JsonReadFloat(j, "rotation");
}

void Transform::NetworkSerialize(RakNet::BitStream& _bStream) const
{
	_bStream.Write(position.x);
	_bStream.Write(position.y);

	_bStream.Write(rotation);

	_bStream.Write(scale.x);
	_bStream.Write(scale.y);
}

void Transform::NetworkDeserialize(RakNet::BitStream& _bStream)
{
	glm::vec2 pos(0, 0);
	glm::vec2 scl(1, 1);
	float rot = 0.0f;

	_bStream.Read(pos.x);
	_bStream.Read(pos.y);

	_bStream.Read(rot);

	_bStream.Read(scl.x);
	_bStream.Read(scl.y);

	SetPosition(pos);
	SetRotation(rot);
	SetScale(scl);
}
