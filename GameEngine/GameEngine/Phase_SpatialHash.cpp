#include "EngineCore.h"
#include "Phase_SpatialHash.h"

Phase_SpatialHash::~Phase_SpatialHash()
{

}

void Phase_SpatialHash::Add(int index, CollisionMath::AABB aabb)
{
	int startX = std::floor(aabb.min.x / cellSize);
	int endX = std::floor(aabb.max.x / cellSize);

	int startY = std::floor(aabb.min.y / cellSize);
	int endY = std::floor(aabb.max.y / cellSize);

	for (int x = startX; x <= endX; x++)
	{
		for (int y = startY; y <= endY; y++)
		{
			uint64_t key = ((uint64_t)(uint32_t)x << 32) | (uint32_t)y;
			hashmap[key].push_back(index);
		}
	}
}

void Phase_SpatialHash::Update()
{

}

std::set<std::pair<int, int>> Phase_SpatialHash::Query(std::vector<Collider*>& colliders)
{
	std::set<std::pair<int, int>> potentialCollisions;

	for (auto& a : hashmap)
	{
		std::vector<int>& bucket = a.second;
		if (bucket.size() < 2)
		{
			continue;
		}
		for (int i = 0; i < bucket.size() - 1; i++)
		{
			for (int j = i + 1; j < bucket.size(); j++)
			{
				int indexA = bucket[i];
				int indexB = bucket[j];

				if (indexA == indexB)
					continue;
				if (indexA > indexB)
					std::swap(indexA, indexB);

				bool overlaping = CollisionMath::CheckAABB(colliders[indexA], colliders[indexB]);

				if (overlaping)
				{
					potentialCollisions.insert(MakePair(indexA, indexB));
				}
			}
		}
	}
	return potentialCollisions;
}

void Phase_SpatialHash::Clear()
{	
	hashmap.clear();
}

void Phase_SpatialHash::DebugDraw()
{

}

void Phase_SpatialHash::HashVector(int index, glm::vec2 p)
{
	int x = std::floor(p.x / cellSize);
	int y = std::floor(p.y / cellSize);
	uint64_t key = ((uint64_t)(uint32_t)x << 32) | (uint32_t)y;
	hashmap[key].push_back(index);
}
