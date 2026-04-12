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

	void Serialize(json::JSON& j) override;
	void Deserialize(json::JSON& j) override;

protected:
	bool IsServerOnly() const override
	{
		return true;
	}

	void Load(json::JSON& jsonData) override;

private:
	void Update();

private:
	float speed = 0.0f;
};

#endif


