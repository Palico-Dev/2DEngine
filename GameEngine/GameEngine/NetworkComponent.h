#pragma once
#ifndef _NETWORKCOMPONENT_H_
#define _NETWORKCOMPONENT_H_
#include "Component.h"

class NetworkComponent : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(NetworkComponent, Component);
	CLONEABLE(NetworkComponent);

public:
	void Load(json::JSON& data) override;

	//void RegisterRPC(STRCODE rpcHash, std::function<void(RakNet::BitStream&)> callback)
	//{
	//	rpcRegistry[rpcHash] = callback;
	//}
	
public:
	unsigned int networkId = 0;
	std::string prefabName = "";

	//std::unordered_map<STRCODE, std::function<void(RakNet::BitStream&)>> rpcRegistry;

};

#endif



