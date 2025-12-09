#include "GameCore.h"
#include "MeteorFactory.h"
#include "FileManager.h"
#include "AssetManager.h"
#include "PrefabAsset.h"
#include "Random.h"
#include "Entity.h"
#include "Meteor.h"

IMPLEMENT_DYNAMIC_CLASS(MeteorFactory)

void MeteorFactory::Start()
{
	createTimer = Random::Float(3.0f, 5.0f);
}

void MeteorFactory::Update()
{
	createTimer -= Time::Instance().DeltaTime();
	if (createTimer <= 0.0f)
	{
		createTimer = Random::Float(3.0f, 5.0f);

		CreateMeteor();
	}
}

void MeteorFactory::Load(json::JSON& j)
{
	std::string smallPath = FileManager::JsonReadString(j, "small");
	meteorSmall = AssetManager::Instance().GetAsset<PrefabAsset>(smallPath);
	std::string bigPath = FileManager::JsonReadString(j, "big");
	meteorBig = AssetManager::Instance().GetAsset<PrefabAsset>(bigPath);
}

void MeteorFactory::CreateMeteor()
{
	int count = Random::Int(1, 3);

	std::vector<glm::vec2> posList;
	float minDist = 50.0f;

	for (int i = 0; i < count; i++)
	{
		glm::vec2 pos;
		bool valid = false;

		while (!valid)
		{
			pos = { Random::Float(10.0f, 740.0f), 0.0f };
			bool collisionFound = false;
			for (const auto& existingPos : posList)
			{
				if (glm::distance(pos, existingPos) < minDist)
				{
					collisionFound = true;
					break; 
				}
			}

			if (!collisionFound)
			{
				valid = true;
			}
		}
		posList.push_back(pos);
	}

	for (int i = 0; i < count; i++)
	{

		if (Random::Bool())
		{
			Entity* e = Gameplay::Spawn(meteorBig, posList[i]);
			e->GetComponent<Meteor>()->SetSpeed(Random::Float(80.0f,120.0f));
		}
		else
		{
			Entity* e = Gameplay::Spawn(meteorSmall, posList[i]);
			e->GetComponent<Meteor>()->SetSpeed(Random::Float(130.0f, 150.0f));
		}
	}

}
