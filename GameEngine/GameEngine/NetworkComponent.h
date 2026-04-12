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
	
public:
	unsigned int networkId = 0;
	std::string prefabName = "";

};

#endif



