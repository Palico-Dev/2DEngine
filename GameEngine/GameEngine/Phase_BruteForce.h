#pragma once
#ifndef _PHASE_BRUTEFORCE_H_
#define _PHASE_BRUTEFORCE_H_

#include "BroadPhase.h"

class Collider;

class Phase_BruteForce : public BroadPhase
{
public:
	Phase_BruteForce();
	virtual ~Phase_BruteForce();

	void Add(int index, CollisionMath::AABB aabb) override;
	void Update() override;
	std::set<std::pair<int, int>> Query(std::vector<Collider*>& colliders) override;


	void DebugDraw() override;
};
#endif


