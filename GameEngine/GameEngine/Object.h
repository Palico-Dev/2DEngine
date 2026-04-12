#pragma once

#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <iostream>
#include "json.hpp"
#include "INetworkSerializable.h"

class Object : public INetworkSerializable
{
	DECLARE_ABSTRACT_BASE_CLASS(Object)

public:
	virtual void Initialize();
	virtual void Destroy();
	
	virtual void Load(json::JSON& jsonData);

	STRCODE GetId() { return uid; }
	void SetId(int _uid) { uid = _uid; }

protected:
	void NetworkSerialize(RakNet::BitStream& _bStream)const override
	{
	};
	void NetworkDeserialize(RakNet::BitStream& _bStream) override
	{
	};

protected:
	bool initialized = false;

private:
	STRCODE uid = -1;
	std::string guid;
};

#endif	// _OBJECT_H_
