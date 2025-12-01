#include "EngineCore.h"
#include "CollisionMath.h"
#include "SDL.h"
#include "Collider.h"
#include "CircleCollider.h"
#include "BoxCollider.h"

glm::vec2 CollisionMath::PointToVector2(SDL_Point p)
{
	return{ (float)p.x,(float)p.y };
}

SDL_Point CollisionMath::Vector2ToPoint(const glm::vec2& v)
{
	return { (int)v.x,(int)v.y };
}

bool CollisionMath::CheckAABB(Collider* a, Collider* b)
{
	if (a->layer != b->layer)
		return false;
	AABB boxA = a->GetAABB();
	AABB boxB = b->GetAABB();
	return CheckAABBOverlap(boxA, boxB);
}

bool CollisionMath::CheckAABBOverlap(AABB a, AABB b)
{
	if (b.min.x >= a.max.x || a.min.x >= b.max.x || b.min.y >= a.max.y || a.min.y >= b.max.y)
	{
		return false;
	}
	return true;
}

CollisionMath::CollisionInfo CollisionMath::SAT_BoxBox(BoxCollider* a, BoxCollider* b)
{
	CollisionInfo info;
	std::vector<glm::vec2> verticesA = a->GetVertices();
	std::vector<glm::vec2> verticesB = b->GetVertices();

	for (int i = 0; i < verticesA.size(); i++)
	{
		glm::vec2 current = verticesA[i];
		glm::vec2 next = verticesA[(i + 1) % verticesA.size()];
		glm::vec2 v = normalize(VerticalLine(current, next));

		float minA, maxA, minB, maxB;
		Projection(verticesA, v, minA, maxA);
		Projection(verticesB, v, minB, maxB);
		if (maxA <= minB || maxB <= minA)
		{
			info.isOverlapping = false;
			return info;
		}
		else
		{
			//Penetration
			info.isOverlapping = true;

			float overlap = fmin(maxA - minB, maxB - minA);

			glm::vec2 AB = b->GetCenterWorld() - a->GetCenterWorld();
			glm::vec2 normal = dot(v, AB) < 0 ? -v : v;

			if (overlap < info.penetration)
			{
				info.penetration = overlap;
				info.normal = normal;
			}
		}
	}
	for (int i = 0; i < verticesB.size(); i++)
	{
		glm::vec2 current = verticesB[i];
		glm::vec2 next = verticesB[(i + 1) % verticesB.size()];
		glm::vec2 v = normalize(VerticalLine(current, next));

		float minA, maxA, minB, maxB;
		Projection(verticesA, v, minA, maxA);
		Projection(verticesB, v, minB, maxB);
		if (maxA <= minB || maxB <= minA)
		{
			info.isOverlapping = false;
			return info;
		}
		else
		{
			info.isOverlapping = true;

			float overlap = fmin(maxA - minB, maxB - minA);

			glm::vec2 AB = b->GetCenterWorld() - a->GetCenterWorld();
			glm::vec2 normal = dot(v, AB) < 0 ? -v : v;

			if (overlap < info.penetration)
			{
				info.penetration = overlap;
				info.normal = normal;
			}
		}
	}
	info.penetration += 1;
	return info;
}

CollisionMath::CollisionInfo CollisionMath::SAT_BoxCircle(BoxCollider* a, CircleCollider* b)
{
	CollisionInfo info;
	std::vector<glm::vec2> verticesA = a->GetVertices();
	glm::vec2 AB = b->GetCenterWorld() - a->GetCenterWorld();

	for (int i = 0; i < verticesA.size(); i++)
	{
		glm::vec2 current = verticesA[i];
		glm::vec2 next = verticesA[(i + 1) % verticesA.size()];
		glm::vec2 v = normalize(VerticalLine(current, next));

		float minA, maxA, minB, maxB;
		Projection(verticesA, v, minA, maxA);
		Projection(b->GetCenterWorld(), b->GetRadiusWorld(), v, minB, maxB);
		if (maxA <= minB || maxB <= minA)
		{
			info.isOverlapping = false;
			return info;
		}
		else
		{
			//Penetration
			info.isOverlapping = true;

			float overlap = fmin(maxA - minB, maxB - minA);
			glm::vec2 normal = dot(v, AB) < 0 ? -v : v;

			if (info.penetration == 0 || overlap < info.penetration)
			{
				info.penetration = overlap;
				info.normal = normal;
			}
		}
	}

	glm::vec2 closestVertex = verticesA[0];
	float minDistance = glm::length(b->GetCenterWorld() - verticesA[0]);

	for (int i = 1; i < verticesA.size(); i++)
	{
		float dist = glm::length(b->GetCenterWorld() - verticesA[i]);
		if (dist < minDistance)
		{
			minDistance = dist;
			closestVertex = verticesA[i];
		}
	}

	glm::vec2 axis = b->GetCenterWorld() - closestVertex;

	glm::vec2 v = glm::normalize(axis);

	float minA, maxA, minB, maxB;
	Projection(verticesA, v, minA, maxA);
	Projection(b->GetCenterWorld(), b->GetRadiusWorld(), v, minB, maxB);

	if (maxA <= minB || maxB <= minA)
	{
		info.isOverlapping = false;
		return info;
	}

	float overlap = fmin(maxA - minB, maxB - minA);

	if (overlap < info.penetration)
	{
		info.penetration = overlap;
		info.normal = dot(v, AB) < 0 ? -v : v;
	}


	return info;
}

CollisionMath::CollisionInfo CollisionMath::CircleCircle(CircleCollider* a, CircleCollider* b)
{
	CollisionInfo info;
	glm::vec2 centerA = a->GetCenterWorld();
	glm::vec2 centerB = b->GetCenterWorld();
	float distance = length(centerA - centerB);
	if (distance >= (a->GetRadiusWorld() + b->GetRadiusWorld()))
	{
		info.isOverlapping = false;
	}
	else
	{
		info.isOverlapping = true;
		info.normal = normalize(centerB - centerA);
		info.penetration = a->GetRadiusWorld() + b->GetRadiusWorld() - distance;
	}
	return info;
}

bool CollisionMath::CheckPointInShapes(glm::vec2 point, Collider* collider)
{
	if (collider->GetType() == ColliderType::Circle)
	{
		return (point - collider->GetCenterWorld()).length() < ((CircleCollider*)collider)->GetRadiusWorld();
	}
	else if (collider->GetType() == ColliderType::Box)
	{
		std::vector<glm::vec2> vertices = ((BoxCollider*)collider)->GetVertices();

		for (int i = 0; i < vertices.size(); i++)
		{
			glm::vec2 a = vertices[i];
			glm::vec2 b = vertices[(i + 1) % vertices.size()];

			glm::vec2 edge = b - a;
			glm::vec2 p = point - a;

			float v = edge.x * p.y - edge.y * p.x;
			if (v <= 0)
				return false;
		}
		return true;
	}
	return true;
}

glm::vec2 CollisionMath::VerticalLine(const glm::vec2& pointA, const glm::vec2& pointB)
{
	return{ -(pointB - pointA).y,(pointB - pointA).x };
}

void CollisionMath::Projection(const std::vector<glm::vec2> vertices, glm::vec2 line, float& outMin, float& outMax)
{
	if (vertices.size() <= 1)
		return;
	float resMin = dot(vertices[0], line);
	float resMax = resMin;

	for (auto v : vertices)
	{
		float res = dot(v, line);
		resMin = fmin(res, resMin);
		resMax = fmax(res, resMax);
	}
	outMax = resMax;
	outMin = resMin;
}

void CollisionMath::Projection(const glm::vec2 center, float radius, glm::vec2 line, float& outMin, float& outMax)
{
	float centerP = dot(center, line);
	outMin = centerP - radius;
	outMax = centerP + radius;
}

