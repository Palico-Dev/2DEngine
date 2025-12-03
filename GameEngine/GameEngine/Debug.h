#pragma once
#ifndef _DEBUG_H_
#define _DEBUG_H_

class Debug
{
public:
	static void Log(const std::string& msg)
	{
#ifdef _DEBUG
		std::cout << "Log: " << msg << std::endl;
#endif
	}
	static void Warning(const std::string& msg)
	{
#ifdef _DEBUG
		std::cout << "Warning: " << msg << std::endl;
#endif
	}
	static void Error(const std::string& msg)
	{
#ifdef _DEBUG
		std::cout << "Error: " << msg << std::endl;
		std::abort();
#endif
	}
};

#endif


