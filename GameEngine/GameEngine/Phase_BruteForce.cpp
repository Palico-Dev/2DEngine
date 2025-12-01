#include "EngineCore.h"
#include "Phase_BruteForce.h"

Phase_BruteForce::Phase_BruteForce()
{

}

Phase_BruteForce::~Phase_BruteForce()
{

}

void Phase_BruteForce::Add(int index, CollisionMath::AABB aabb)
{

}


void Phase_BruteForce::Update()
{

}

std::set<std::pair<int, int>> Phase_BruteForce::Query(std::vector<Collider*>& colliders)
{
	std::set<std::pair<int, int>> potentialCollisions;
	for (int i = 0; i < colliders.size() - 1; i++)
	{
		for (int j = i + 1; j < colliders.size(); j++)
		{
			bool overlaping = CollisionMath::CheckAABB(colliders[i], colliders[j]);

			if (overlaping)
			{
				potentialCollisions.insert(MakePair(i,j));
			}
		}
	}

	return potentialCollisions;
}

void Phase_BruteForce::DebugDraw()
{

}
