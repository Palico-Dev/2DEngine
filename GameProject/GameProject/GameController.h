#pragma once
#ifndef _GAMECONTROLLER_H_
#define _GAMECONTROLLER_H_

#include "Component.h"

class GameController : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(GameController, Component);
	//DECLARE_SINGLETON(GameController)
};

#endif


