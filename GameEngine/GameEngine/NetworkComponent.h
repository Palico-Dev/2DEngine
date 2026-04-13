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

	void RegisterRPC(const std::string& functionName, std::function<void(RakNet::BitStream&)> callback);
	
public:
	unsigned int networkId = 0;
	std::string prefabName = "";

	bool syncTransformContinously = true;

	std::unordered_map<STRCODE, std::function<void(RakNet::BitStream&)>> rpcRegistry;

};

#endif



