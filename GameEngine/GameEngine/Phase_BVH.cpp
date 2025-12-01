#include "EngineCore.h"
#include "Phase_BVH.h"

Phase_BVH::Phase_BVH()
{

}

Phase_BVH::~Phase_BVH()
{

}

void Phase_BVH::Add(int index, CollisionMath::AABB aabb)
{

}

void Phase_BVH::Update()
{

}

std::set<std::pair<int, int>> Phase_BVH::Query(std::vector<Collider*>& colliders)
{
	return std::set<std::pair<int, int>>();
}

void Phase_BVH::DebugDraw()
{

}
