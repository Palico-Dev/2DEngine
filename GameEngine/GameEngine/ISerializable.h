#pragma once

#ifndef _ISERIALIZABLE_H_
#define _ISERIALIZABLE_H_

#include<BitStream.h>

class ISerializable
{
public:
	virtual ~ISerializable() {}
	virtual void Serialize(RakNet::BitStream& bitStream) const = 0;
	virtual void Deserialize(RakNet::BitStream& bitStream) = 0;

	virtual void SerializeCreate(RakNet::BitStream& _bStream) const {};
	virtual void DeserializeCreate(RakNet::BitStream& _bStream) {};

};

#endif
