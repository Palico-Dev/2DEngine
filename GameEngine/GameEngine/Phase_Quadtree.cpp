#include "EngineCore.h"
#include "Phase_Quadtree.h"
#include "QuadTree.h"

Phase_Quadtree::Phase_Quadtree(AABB bound)
{
	quadtree = new QuadTree(bound);
}

Phase_Quadtree::Phase_Quadtree()
{
	quadtree = new QuadTree({{0,0},{20,20}});
}

Phase_Quadtree::~Phase_Quadtree()
{
	quadtree->Clear();
	delete quadtree;
}

void Phase_Quadtree::Add(int index, CollisionMath::AABB aabb)
{
	while (!CheckAABBOverlap(quadtree->GetBound(),aabb))
	{
		ExpandTree(aabb);
	}
	quadtree->Insert(index, aabb);
}

void Phase_Quadtree::Update()
{

}

std::set<std::pair<int, int>> Phase_Quadtree::Query(std::vector<Collider*>& colliders)
{
	std::set<std::pair<int, int>> potentialCollisions;
	for (int i = 0; i < colliders.size(); i++)
	{
		std::vector<QuadTree*> nodes;
		quadtree->FindNode(colliders[i]->GetAABB(), nodes);
		for (int j = 0; j < nodes.size(); j++)
		{
			std::vector<int> colliderindexs = nodes[j]->GetIndexs();
			if (colliderindexs.size() < 2)
				continue;

			for (int k = 0; k < colliderindexs.size(); k++)
			{
				int neighborIndex = colliderindexs[k];

				if (i == neighborIndex) continue;

				if (neighborIndex <= i) continue;

				if (CollisionMath::CheckAABB(colliders[i], colliders[neighborIndex]))
				{
					potentialCollisions.insert(std::make_pair(i, neighborIndex));
				}
			}
			
		}
	}


	return potentialCollisions;
}

void Phase_Quadtree::DebugDraw()
{

}

void Phase_Quadtree::Clear()
{
	quadtree->Clear();
}

void Phase_Quadtree::ExpandTree(AABB aabb)
{
	glm::vec2 objCenter = (aabb.min + aabb.max) * 0.5f;
	glm::vec2 rootMin = quadtree->GetBound().min;
	glm::vec2 rootMax = quadtree->GetBound().max;

	bool growLeft = objCenter.x < rootMin.x;
	bool growUp = objCenter.y < rootMin.y;

	glm::vec2 size = rootMax - rootMin;
	glm::vec2 newMin = rootMin;
	glm::vec2 newMax = rootMax;

	if (growLeft) 
		newMin.x -= size.x;
	else          
		newMax.x += size.x;

	if (growUp)   
		newMin.y -= size.y;
	else          
		newMax.y += size.y;

	AABB newBound = { newMin, newMax };

	QuadTree* newRoot = new QuadTree(newBound);

	glm::vec2 center = (newMin + newMax) * 0.5f;

	AABB qTL = { newMin, center };
	AABB qTR = { {center.x, newMin.y}, {newMax.x, center.y} };
	AABB qBL = { {newMin.x, center.y}, {center.x, newMax.y} };
	AABB qBR = { center, newMax };

	QuadTree* childTL = nullptr;
	QuadTree* childTR = nullptr;
	QuadTree* childBL = nullptr;
	QuadTree* childBR = nullptr;

	if (growLeft && growUp)
	{
		childTL = new QuadTree(qTL);
		childTR = new QuadTree(qTR);
		childBL = new QuadTree(qBL);
		childBR = quadtree; 
	}
	else if (!growLeft && growUp)
	{
		childTL = new QuadTree(qTL);
		childTR = new QuadTree(qTR);
		childBL = quadtree; 
		childBR = new QuadTree(qBR);
	}
	else if (growLeft && !growUp)
	{
		childTL = new QuadTree(qTL);
		childTR = quadtree; 
		childBL = new QuadTree(qBL);
		childBR = new QuadTree(qBR);
	}
	else 
	{
		childTL = quadtree; 
		childTR = new QuadTree(qTR);
		childBL = new QuadTree(qBL);
		childBR = new QuadTree(qBR);
	}

	newRoot->SetChild({ childTL, childTR, childBL, childBR });

	quadtree = newRoot;
}
