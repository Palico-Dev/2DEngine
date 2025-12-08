#pragma once
#ifndef _METEORFACTORY_H_
#define _METEORFACTORY_H_

#include "Component.h"

class PrefabAsset;

class MeteorFactory : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(MeteorFactory, Component);

public:
	void Start() override;
	void Update() override;
	void Load(json::JSON& j) override;

private:
	void CreateMeteor();

private:
	PrefabAsset* meteorSmall = nullptr;
	PrefabAsset* meteorBig = nullptr;

	float createTimer = 0.0f;
};

#endif


