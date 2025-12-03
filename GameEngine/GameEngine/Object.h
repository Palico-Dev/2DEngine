#pragma once

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <iostream>
#include "json.hpp"

class Object
{
	DECLARE_ABSTRACT_BASE_CLASS(Object)

public:
	virtual void Initialize();
	virtual void Destroy();
	
	virtual void Load(json::JSON& jsonData);

	STRCODE GetId() { return uid; }
	void SetId(int _uid) { uid = _uid; }

protected:
	bool initialized = false;

private:
	STRCODE uid = -1;
	std::string guid;
};

#endif	// _OBJECT_H_
