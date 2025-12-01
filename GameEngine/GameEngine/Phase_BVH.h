#pragma once
#ifndef _PHASE_BVH_H_
#define _PHASE_BVH_H_

#include "BroadPhase.h"

class Phase_BVH : public BroadPhase
{
public:
	Phase_BVH();
	virtual ~Phase_BVH();

	void Add(int index, CollisionMath::AABB aabb) override;
	void Update() override;

	std::set<std::pair<int, int>> Query(std::vector<Collider*>& colliders) override;
	void DebugDraw() override;
};

#endif


