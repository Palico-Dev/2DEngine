#pragma once
#ifndef _RANDOM_H_
#define _RANDOM_H_

class Random
{
public:
	static bool Bool();
	static int Int(int min, int max);
	static float Float(float min, float max);
	static float Float();
	static glm::vec2 Vec2(float minX, float maxX, float minY, float maxY);

private:
	static std::mt19937& GetEngine();
};

#endif


