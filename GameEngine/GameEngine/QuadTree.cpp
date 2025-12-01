#include "EngineCore.h"
#include "QuadTree.h"

QuadTree::~QuadTree()
{
	Clear();
}

void QuadTree::Insert(int index, AABB aabb)
{
	if (CheckAABBOverlap(bound, aabb))
	{
		if (children.size() == 0)
		{
			colliderindexs.push_back({ index,aabb});
			if ((bound.max.y-bound.min.y) >minSize&& colliderindexs.size() > maxObejct)
			{
				Split();
			}
		}
		else
		{
			for (auto& child : children)
			{
				child->Insert(index, aabb);
			}
		}
	}
}

void QuadTree::Clear()
{
	colliderindexs.clear();
	for (auto& child : children)
	{
		child->Clear();
		delete child;
	}
	children.clear();
}

std::vector<int> QuadTree::GetIndexs()
{
	std::vector<int> res;
	for (auto& a : colliderindexs)
	{
		res.push_back(a.first);
	}
	return res;
}


void QuadTree::FindNode(AABB aabb, std::vector<QuadTree*>& outNodes)
{
	if (CheckAABBOverlap(aabb, bound))
	{
		if (children.size() == 0)
		{
			outNodes.push_back(this);
		}
		else
		{
			for (auto& child : children)
			{
				child->FindNode(aabb, outNodes);
			}
		}
	}
}

void QuadTree::Split()
{
	glm::vec2 center = (bound.min + bound.max) * 0.5f;
	AABB topleft = { bound.min,center };
	AABB topright = { {center.x,bound.min.y},{bound.max.x,center.y} };
	AABB bottomleft = { {bound.min.x,center.y},{center.x,bound.max.y} };
	AABB bottomright = { center,bound.max };

	QuadTree* tlTree = new QuadTree(topleft);
	QuadTree* trTree = new QuadTree(topright);
	QuadTree* blTree = new QuadTree(bottomleft);
	QuadTree* brTree = new QuadTree(bottomright);
	children.push_back(tlTree);
	children.push_back(trTree);
	children.push_back(blTree);
	children.push_back(brTree);

	for (auto& i : colliderindexs)
	{
		tlTree->Insert(i.first, i.second);
		trTree->Insert(i.first, i.second);
		blTree->Insert(i.first, i.second);
		brTree->Insert(i.first, i.second);
	}
	colliderindexs.clear();
}


