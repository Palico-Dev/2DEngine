#pragma once
#ifndef _PHASE_SPATIALHASH_H_
#define _PHASE_SPATIALHASH_H_

#include "BroadPhase.h"
#include <unordered_map>

class Phase_SpatialHash : public BroadPhase
{
public:
	Phase_SpatialHash(unsigned int _cellSize) : cellSize(_cellSize) { }
	virtual ~Phase_SpatialHash();

	void Add(int index, CollisionMath::AABB aabb) override;
	void Update() override;
	std::set<std::pair<int, int>> Query(std::vector<Collider*>& colliders) override;

	void Clear();

	void DebugDraw() override;

private:
	void HashVector(int index, glm::vec2 p);
private:
	std::unordered_map<uint64_t, std::vector<int>> hashmap;
	unsigned int cellSize;
};
#endif


