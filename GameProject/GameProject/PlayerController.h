#pragma once
#ifndef _PLAYERCONTROLLER_H_
#define _PLAYERCONTROLLER_H_
#include "Component.h"

class PlayerController : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(PlayerController, Component)

public:
	void Update() override;
	void Initialize() override;
	Component* Clone() override;

public:
	float speed = 100.0f;
	
};

#endif


