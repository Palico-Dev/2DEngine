#include "EngineCore.h"
#include "CollisionSystem.h"
#include "BoxCollider.h"
#include "CircleCollider.h"
#include "Phase_BruteForce.h"
#include "Phase_BVH.h"
#include "Phase_Quadtree.h"
#include "Phase_SpatialHash.h"

bool CollisionSystem::CheckPoint(SDL_Point pos)
{
	for (int i = 0; i < colliders.size(); i++)
	{
		if (CheckPointInShapes({ pos.x,pos.y }, colliders[i]))
		{
			return true;
		}
	}
	return false;
}


bool CollisionSystem::CheckPoint(SDL_Point pos, Entity* outEntity)
{
	for (int i = 0; i < colliders.size(); i++)
	{
		if (CheckPointInShapes({ pos.x,pos.y }, colliders[i]))
		{
			outEntity = colliders[i]->owner;
			return true;
		}
	}
	return false;
}


bool CollisionSystem::CheckCollision(Entity* e)
{
	std::vector<Collider*> entityColliders = e->GetAllComponents<Collider>();

	for (int i = 0; i < entityColliders.size(); i++)
	{
		if (CheckCollision(entityColliders[i]))
		{
			return true;
		}
	}
	return false;
}

bool CollisionSystem::CheckCollision(Collider* c)
{
	for (int i = 0; i < colliders.size(); i++)
	{
		CollisionInfo info = CheckCollision(c, colliders[i]);

		if (info.isOverlapping == true)
		{
			return true;
		}
	}
	return false;
}

bool CollisionSystem::CheckCollision(Entity* a, Entity* b)
{
	std::vector<Collider*> entityColliders = a->GetAllComponents<Collider>();
	for (int i = 0; i < entityColliders.size(); i++)
	{
		if (CheckCollision(entityColliders[i], b))
		{
			return true;
		}
	}
	return false;
}



bool CollisionSystem::CheckCollision(Collider* c, Entity* e)
{
	std::vector<Collider*> entityColliders = e->GetAllComponents<Collider>();
	for (int i = 0; i < entityColliders.size(); i++)
	{
		CollisionInfo info = CheckCollision(c, entityColliders[i]);

		if (info.isOverlapping == true)
		{
			return true;
		}
	}
	return false;
}

CollisionInfo CollisionSystem::CheckCollision(Collider* a, Collider* b)
{
	CollisionInfo info;
	if (a == b)
		return info;

	if (a->GetType() == ColliderType::Box && b->GetType() == ColliderType::Box)
	{
		info = SAT_BoxBox((BoxCollider*)a, (BoxCollider*)b);
	}
	else if (a->GetType() == ColliderType::Box && b->GetType() == ColliderType::Circle)
	{
		info = SAT_BoxCircle((BoxCollider*)a, (CircleCollider*)b);
	}
	else if (a->GetType() == ColliderType::Circle && b->GetType() == ColliderType::Box)
	{
		info = SAT_BoxCircle((BoxCollider*)b, (CircleCollider*)a);
		info.normal = -info.normal;
	}
	else if (a->GetType() == ColliderType::Circle && b->GetType() == ColliderType::Circle)
	{
		info = CircleCircle((CircleCollider*)a, (CircleCollider*)b);
	}

	return info;
}

void CollisionSystem::RemoveCollider(Collider* c)
{
	colliders.erase(std::remove(colliders.begin(), colliders.end(), c),
		colliders.end());

	for (auto it = lastFrameResult.begin(); it != lastFrameResult.end(); )
	{
		if (it->first.first == c || it->first.second == c)
		{
			it = lastFrameResult.erase(it);
		}
		else
		{
			++it;
		}
	}
}

void CollisionSystem::Clear()
{
	lastFrameResult.clear();
	currentFrameResult.clear();
}

void CollisionSystem::Initialize()
{
#if COLLISIONTEST
	RandomCollider(1000);
#endif
	bruteForce = new Phase_BruteForce();
	spatialHash = new Phase_SpatialHash(20);
	quadtree = new Phase_Quadtree({ {0,0},{1000,800} });
	bvh = new Phase_BVH();
}

void CollisionSystem::Update()
{
	currentFrameResult.clear();

	Detect();
	FireEvents();
	Resolve();

	lastFrameResult = currentFrameResult;
}

void CollisionSystem::Destroy()
{
}

void CollisionSystem::Detect()
{
	if (colliders.size() <= 1)
		return;

	std::set<std::pair<int, int>> potentialCollisions;

#if COLLISIONTEST
	long long currentMillSeconds;

	//Brute Force
	currentMillSeconds = Time::Instance().TotalTimeMill();
	potentialCollisions = bruteForce->Query(colliders);
	std::cout << "Brute Force: " << Time::Instance().TotalTimeMill() - currentMillSeconds << " ms  Potential Collisions: " << potentialCollisions.size() << std::endl;

	//Spatial Hash
	currentMillSeconds = Time::Instance().TotalTimeMill();
#endif

	spatialHash->Clear();
	for (int i = 0; i < colliders.size(); i++)
	{
		spatialHash->Add(i, colliders[i]->GetAABB());
	}
	potentialCollisions = spatialHash->Query(colliders);

#if COLLISIONTEST
	std::cout << "Spatial hash: " << Time::Instance().TotalTimeMill() - currentMillSeconds << " ms  Potential Collisions: " << potentialCollisions.size() << std::endl;

	//Quadtree
	currentMillSeconds = Time::Instance().TotalTimeMill();
	quadtree->Clear();
	for (int i = 0; i < colliders.size(); i++)
	{
		quadtree->Add(i, colliders[i]->GetAABB());
	}
	potentialCollisions = quadtree->Query(colliders);
	std::cout << "Quadtree: " << Time::Instance().TotalTimeMill() - currentMillSeconds << " ms  Potential Collisions: " << potentialCollisions.size() << std::endl;
#endif


	//Narrow phase
	for (auto& collision : potentialCollisions)
	{
		CollisionInfo info = CheckCollision(colliders[collision.first], colliders[collision.second]);

		if (info.isOverlapping == true)
		{
			currentFrameResult.emplace(MakePairKey(colliders[collision.first], colliders[collision.second],info), info);
		}

	}
}

void CollisionSystem::FireEvents()
{
	//FireEvents
	for (auto& res : currentFrameResult)
	{
#if COLLISIONTEST
		//std::cout << res.first.first->name << "," << res.first.second->name << ": " << res.second.isOverlapping << " " << res.second.penetration << std::endl;
#endif
		auto it = lastFrameResult.find(res.first);
		if (it != lastFrameResult.end())
		{
			//FireStay
			Collider* a = res.first.first;
			Collider* b = res.first.second;

			if (a->isTrigger || b->isTrigger)
			{
				a->owner->DispatchTriggerStay(b);
				b->owner->DispatchTriggerStay(a);
			}
			else
			{
				a->owner->DispatchCollisionStay(b);
				b->owner->DispatchCollisionStay(a);
			}
			lastFrameResult.erase(it);
		}
		else
		{
			//FireEnter

			Collider* a = res.first.first;
			Collider* b = res.first.second;

			if (a->isTrigger || b->isTrigger)
			{
				a->owner->DispatchTriggerEnter(b);
				b->owner->DispatchTriggerEnter(a);
			}
			else
			{
				a->owner->DispatchCollisionEnter(b);
				b->owner->DispatchCollisionEnter(a);
			}
		}
	}

	//FireExit
	for (auto& res : lastFrameResult)
	{
		Collider* a = res.first.first;
		Collider* b = res.first.second;

		if (a == nullptr || b == nullptr)
			continue;


		if (a->isTrigger || b->isTrigger)
		{
			a->owner->DispatchTriggerExit(b);
			b->owner->DispatchTriggerExit(a);
		}
		else
		{
			a->owner->DispatchCollisionExit(b);
			b->owner->DispatchCollisionExit(a);
		}
	}
}

void CollisionSystem::Resolve()
{
#if COLLISIONTEST
	//return;
	std::exit(0);
#endif
	//Resolve
	for (auto& res : currentFrameResult)
	{
		Collider* a = res.first.first;
		Collider* b = res.first.second;
		CollisionInfo info = res.second;

		if (a->isTrigger || b->isTrigger)
			continue;

		if (a->isStatic && b->isStatic)
			continue;

		if (a->isStatic)
		{
			b->owner->transform->SetPosition(b->owner->transform->GetPosition() + info.normal * info.penetration);

		}
		else if (b->isStatic)
		{
			a->owner->transform->SetPosition(a->owner->transform->GetPosition() + (-info.normal) * info.penetration);
		}
		else
		{
			float totalMass = a->mass + b->mass;

			a->owner->transform->SetPosition(a->owner->transform->GetPosition() + (-info.normal) * info.penetration * b->mass / totalMass);
			b->owner->transform->SetPosition(b->owner->transform->GetPosition() + info.normal * info.penetration * a->mass / totalMass);
		}

	}
}

std::pair<Collider*, Collider*> CollisionSystem::MakePairKey(Collider* c1, Collider* c2, CollisionInfo& info)
{
	if (c1->GetId() < c2->GetId())
	{
		return{ c1,c2 };
	}
	else
	{
		info.normal = -info.normal;
		return{ c2,c1 };
	}
}

#if COLLISIONTEST
void CollisionSystem::Test()
{

}

void CollisionSystem::RandomCollider()
{
	// --- Test Case 1: Box vs Box (Corner Overlap) ---
// Scenario: Two squares overlapping at a corner.
	BoxCollider* boxA = (BoxCollider*)CreateObject("BoxCollider");
	boxA->Initialize();
	boxA->name = "BoxA";
	// A 2x2 square at origin
	boxA->SetVertices({ {0,0}, {2,0}, {2,2}, {0,2} });
	boxA->SetCenter({ 1.0f, 1.0f });

	BoxCollider* boxB = (BoxCollider*)CreateObject("BoxCollider");
	boxB->Initialize();
	boxB->name = "BoxB";
	// A 2x2 square shifted up and right
	boxB->SetVertices({ {1,1}, {3,1}, {3,3}, {1,3} });
	boxB->SetCenter({ 2.0f, 2.0f });

	// --- Test Case 2: Circle vs Circle (Direct Horizontal Overlap) ---
	// Scenario: Two circles overlapping on the X-axis.
	CircleCollider* circleA = (CircleCollider*)CreateObject("CircleCollider");
	circleA->Initialize();
	circleA->name = "CircleA";
	circleA->SetCenter({ 5.0f, 5.0f });
	circleA->SetRadius(1.0f);

	CircleCollider* circleB = (CircleCollider*)CreateObject("CircleCollider");
	circleB->Initialize();
	circleB->name = "CircleB";
	circleB->SetCenter({ 6.5f, 5.0f });
	circleB->SetRadius(1.0f);

	// --- Test Case 3: Box vs Circle (Edge Penetration) ---
	// Scenario: A circle hitting the right-side flat edge of a tall box.
	BoxCollider* boxC = (BoxCollider*)CreateObject("BoxCollider");
	boxC->Initialize();
	boxC->name = "BoxC";
	// A tall rectangle from x=10 to x=12
	boxC->SetVertices({ {10,0}, {12,0}, {12,4}, {10,4} });
	boxC->SetCenter({ 11.0f, 2.0f });

	CircleCollider* circleC = (CircleCollider*)CreateObject("CircleCollider");
	circleC->Initialize();
	circleC->name = "CircleC";
	// Center is 0.5 units away from the box's right edge (x=12)
	circleC->SetCenter({ 12.5f, 2.0f });
	circleC->SetRadius(1.0f);



}

void CollisionSystem::RandomCollider(int count)
{
	std::random_device rd;
	std::mt19937 gen(rd());

	std::uniform_int_distribution<> typeDist(0, 1);
	std::uniform_real_distribution<float> xDist(0.0f, 1000.0f);
	std::uniform_real_distribution<float> yDist(0.0f, 800.0f);
	std::uniform_real_distribution<float> sizeDist(1.0f, 8.0f);
	std::uniform_real_distribution<float> angleDist(0.0f, 6.28318f);

	for (int i = 0; i < count; i++)
	{
		int colliderType = typeDist(gen);
		float cx = xDist(gen);
		float cy = yDist(gen);

		if (colliderType == 0) // BOX
		{
			BoxCollider* box = (BoxCollider*)CreateObject("BoxCollider");
			box->Initialize();
			box->name = "Box_" + std::to_string(i);
			box->SetCenter({ cx, cy });

			float width = sizeDist(gen);
			float height = sizeDist(gen);
			float halfW = width / 2.0f;
			float halfH = height / 2.0f;

			float theta = angleDist(gen);
			float cosT = cos(theta);
			float sinT = sin(theta);

			float localX[4] = { -halfW,  halfW,  halfW, -halfW };
			float localY[4] = { halfH,  halfH, -halfH, -halfH };

			std::vector<glm::vec2> rotatedVertices;
			for (int k = 0; k < 4; k++)
			{
				float rX = (localX[k] * cosT) - (localY[k] * sinT);
				float rY = (localX[k] * sinT) + (localY[k] * cosT);

				rotatedVertices.push_back({ cx + rX, cy + rY });
			}

			box->SetVertices(rotatedVertices);
			box->isRendered = true;
		}
		else
		{
			CircleCollider* circle = (CircleCollider*)CreateObject("CircleCollider");
			circle->Initialize();
			circle->name = "Circle_" + std::to_string(i);
			circle->SetCenter({ cx, cy });
			circle->SetRadius(sizeDist(gen));
			circle->isRendered = true;
		}
	}
}

#endif

