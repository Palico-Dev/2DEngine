#pragma once
#ifndef _UTILITY_H_
#define _UTILITY_H_

class Utility
{
public:
	template <typename T>
	static bool VectorContains(std::vector<T>& vec, T item)
	{
		return std::find(vec.begin(), vec.end(), item) != vec.end();
	}
};

#endif


