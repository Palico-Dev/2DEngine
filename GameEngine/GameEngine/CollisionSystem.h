#pragma once

#ifndef _COLLISIONSYSTEM_H_
#define _COLLISIONSYSTEM_H_

#include "CollisionMath.h"
#include "SDL.h"
#include "Entity.h"
#define COLLISIONTEST 0

using namespace CollisionMath;

enum ColliderType
{
	Default,
	Box,
	Circle
};

class Collider;
class Phase_BruteForce;
class Phase_SpatialHash;
class Phase_Quadtree;
class Phase_BVH;

class CollisionSystem final
{
public:

	/// <summary>
	/// Check if the pos is overlapping with others
	/// </summary>
	/// <param name="pos"></param>
	/// <returns></returns>
	bool CheckPoint(SDL_Point pos);

	/// <summary>
	/// Check if the pos is overlapping with others
	/// </summary>
	/// <param name="pos"></param>
	/// <param name="outEntity">what is overlaped with you</param>
	/// <returns></returns>
	bool CheckPoint(SDL_Point pos, Entity* outEntity);

	/// <summary>
	/// Check if the entity overlap with others in the scene
	/// </summary>
	/// <param name="e"></param>
	/// <returns></returns>
	bool CheckCollision(Entity* e);

	/// <summary>
	/// Check if the collider overlap with others in the scene
	/// </summary>
	/// <param name="c"></param>
	/// <returns></returns>
	bool CheckCollision(Collider* c);

	/// <summary>
	/// Check if these two entities are overlapping
	/// </summary>
	/// <param name="a"></param>
	/// <param name="b"></param>
	/// <returns></returns>
	bool CheckCollision(Entity* a, Entity* b);

	/// <summary>
	/// Check if the collider is overlapped with the entity
	/// </summary>
	/// <param name="c"></param>
	/// <param name="e"></param>
	/// <returns></returns>
	bool CheckCollision(Collider* c, Entity* e);


	void AddCollider(Collider* c) { colliders.push_back(c); }
	void RemoveCollider(Collider* c);


private:
	void Initialize();
	void Update();
	void Destroy();

	void Clear();
	
	void Detect();
	void FireEvents();
	void Resolve();

	void CallEvent(std::function<void(Collider*)> func,Collider* other);

	friend class Engine;

	std::pair<Collider*, Collider*> MakePairKey(Collider* c1, Collider* c2,CollisionInfo& info);
	CollisionInfo CheckCollision(Collider* a, Collider* b);

#if COLLISIONTEST
	void Test();
	void RandomCollider();
	void RandomCollider(int count);
#endif 

public:
	const std::vector<Collider*>& GetColliders() const { return colliders; }

private:
	std::vector<Collider*> colliders;

	std::map<std::pair<Collider*, Collider*>, CollisionInfo> currentFrameResult;
	std::map<std::pair<Collider*, Collider*>, CollisionInfo> lastFrameResult;
	DECLARE_SINGLETON(CollisionSystem)

	Phase_BruteForce* bruteForce = nullptr;
	Phase_SpatialHash* spatialHash = nullptr;
	Phase_Quadtree* quadtree = nullptr;
	Phase_BVH* bvh = nullptr;
};

#endif //_COLLISIONSYSTEM_H_