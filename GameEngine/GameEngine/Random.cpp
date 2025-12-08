#include "EngineCore.h"
#include "Random.h"

bool Random::Bool()
{
	std::uniform_int_distribution<int> dist(0, 1);
	return dist(GetEngine()) == 1;
}

int Random::Int(int min, int max)
{
	std::uniform_int_distribution<int> dist(min, max);
	return dist(GetEngine());
}

float Random::Float(float min, float max)
{
	std::uniform_real_distribution<float> dist(min, max);
	return dist(GetEngine());
}

float Random::Float()
{
	return Float(0.0f, 1.0f);
}

std::mt19937& Random::GetEngine()
{
	static std::random_device rd; 
	static std::mt19937 engine(rd()); 
	return engine;
}
