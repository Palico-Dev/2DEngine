#pragma once
#ifndef _BROADPHASE_H_
#define _BROADPHASE_H_
#include "CollisionMath.h"
#include <set>

class BroadPhase
{
public:
	virtual ~BroadPhase() = default;

	virtual void Add(int index,CollisionMath::AABB aabb) = 0;
	virtual void Update() = 0;
	virtual std::set<std::pair<int,int>> Query(std::vector<Collider*>& colliders) = 0;

	virtual void DebugDraw() = 0;


protected:
	BroadPhase() = default;

	std::pair<int, int> MakePair(int i, int j)
	{
		if (i < j)
			return{ i,j };
		else
			return { j,i };
	}
};

#endif

