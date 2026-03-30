#pragma once

#include <MessageIdentifiers.h>
#include <map>
#include <functional>

enum NetworkPacketIds
{
	ID_DEFAULT = ID_USER_PACKET_ENUM,
	ID_SCENE_CHANGE,
	ID_SCENE_MANAGER,
	ID_SCENE_UPDATE,
	ID_SCENE_SNAPSHOT,
	ID_CREATE_ENTITY,
	ID_CREATE_COMPONENT,
	ID_DESTROY_ENTITY,
	ID_RPC,
};

template<typename T>
__forceinline T PeakBitStream(RakNet::BitStream& _bStream)
{
	T value;
	_bStream.Read(value);
	_bStream.SetReadOffset(_bStream.GetReadOffset() - sizeof(T) * CHAR_BIT);
	return value;
}
