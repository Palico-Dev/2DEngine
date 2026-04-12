#pragma once

#ifndef _ISERIALIZABLE_H_
#define _ISERIALIZABLE_H_

#include<BitStream.h>

class INetworkSerializable
{
public:
	virtual ~INetworkSerializable() {}
	virtual void NetworkSerialize(RakNet::BitStream& bitStream) const = 0;
	virtual void NetworkDeserialize(RakNet::BitStream& bitStream) = 0;

};

#endif
