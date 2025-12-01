#pragma once
#ifndef _NEXTLEVEL_H_
#define _NEXTLEVEL_H_

#include "Component.h"
#include "Collider.h"

class NextLevel : Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(NextLevel, Component)

public:
	void Initialize() override;

private:
	void OnTriggerEnter(Collider* other);
	void OnTriggerStay(Collider* other);
	void OnTriggerExit(Collider* other);

	void OnComponentInitialized() override;
};

#endif


