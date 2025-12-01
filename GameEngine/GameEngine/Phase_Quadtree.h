#pragma once
#ifndef _PHASE_QUADTREE_H_
#define _PHASE_QUADTREE_H_

#include "BroadPhase.h"
#include "CollisionSystem.h"
#include "Collider.h"

class QuadTree;

class Phase_Quadtree:public BroadPhase
{
public:
	Phase_Quadtree(AABB bound);
	Phase_Quadtree();
	virtual ~Phase_Quadtree();

	void Add(int index, CollisionMath::AABB aabb) override;
	void Update() override;
	std::set<std::pair<int, int>> Query(std::vector<Collider*>& colliders) override;

	void DebugDraw() override;

	void Clear();
private:
	void ExpandTree(AABB aabb);
private:
	QuadTree* quadtree = nullptr;
};

#endif


