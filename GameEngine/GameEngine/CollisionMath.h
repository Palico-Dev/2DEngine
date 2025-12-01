#pragma once
#ifndef _COLLISIONMATH_H_
#define _COLLISIONMATH_H_

class SDL_Point;
class BoxCollider;
class Collider;
class CircleCollider;

namespace CollisionMath
{
	struct AABB
	{
		glm::vec2 min, max;
		AABB(){}
		AABB(glm::vec2 _min, glm::vec2 _max):min(_min),max(_max){}
	};

	struct CollisionInfo
	{
		bool isOverlapping = false;
		glm::vec2 normal;
		float penetration = 1000000.0f;
	};


	glm::vec2 PointToVector2(SDL_Point p);
	SDL_Point Vector2ToPoint(const glm::vec2& v);

	bool CheckAABB(Collider* a, Collider* b);
	bool CheckAABBOverlap(AABB a, AABB b);
	CollisionInfo SAT_BoxBox(BoxCollider* a, BoxCollider* b);
	CollisionInfo SAT_BoxCircle(BoxCollider* a, CircleCollider* b);
	CollisionInfo CircleCircle(CircleCollider* a, CircleCollider* b);

	bool CheckPointInShapes(glm::vec2 point, Collider* collider);


	glm::vec2 VerticalLine(const glm::vec2& pointA, const glm::vec2& pointB);

	void Projection(const std::vector<glm::vec2> vertices, glm::vec2 line, float& outMin, float& outMax);
	void Projection(const glm::vec2 center, float radius, glm::vec2 line, float& outMin, float& outMax);
}
#endif

