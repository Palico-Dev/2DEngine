#pragma once
#ifndef _BACKGROUNDITEM_H_
#define _BACKGROUNDITEM_H_

#include "Component.h"

class TextureAsset;

class BackgroundItem : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(BackgroundItem,Component)
	CLONEABLE(BackgroundItem);

public:
	void Init(TextureAsset* texture,glm::vec2 size,float newSpeed);

private:
	void Update();

private:
	float speed = 0.0f;
};

#endif


