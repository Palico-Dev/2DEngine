#pragma once
#ifndef _QUADTREE_H_
#define _QUADTREE_H_

#include "CollisionSystem.h"

class QuadTree
{
public:
	QuadTree(AABB _bound) :bound(_bound) {}
	~QuadTree();

	void Insert(int index, AABB aabb);
	void FindNode(AABB aabb, std::vector<QuadTree*>& outNodes);

	void Clear();
	std::vector<int> GetIndexs();

	AABB GetBound() { return bound; }

	void SetChild(std::vector<QuadTree*> _children) { children = _children; }

private:
	void Split();
	
private:
	int minSize = 16;
	int maxObejct = 5;

	std::vector<QuadTree*> children;
	std::vector<std::pair<int,AABB>> colliderindexs;
	AABB bound = { {0,0}, {10,10} };


};

#endif


