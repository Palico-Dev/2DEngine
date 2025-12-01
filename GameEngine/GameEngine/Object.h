#pragma once

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <iostream>
#include "json.hpp"

class Object
{
	DECLARE_ABSTRACT_BASE_CLASS(Object)

private:
	bool initialized = false;
	STRCODE uid = -1;
	std::string guid;

public:
	virtual void Initialize();
	virtual void Destroy();
	
	virtual void Load(json::JSON& jsonData);

	bool IsInitialized() { return initialized; }
	STRCODE GetId() { return uid; }
	void SetId(int _uid) { uid = _uid; }

protected:
	void SetInitialized(bool state) { initialized = state; }
};

#endif	// _OBJECT_H_
