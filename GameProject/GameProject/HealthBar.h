#pragma once
#ifndef _HEALTHBAR_H_
#define _HEALTHBAR_H_

#include "Widget.h"

class TextureAsset;

class HealthBar : public Widget
{
	DECLARE_DYNAMIC_DERIVED_CLASS(HealthBar,Widget)

public:
	void Initialize() override;
	void Destroy() override;
	void Update() override;
	void Load(json::JSON& j) override;

protected:
	void OnRender() override;

private:
	int gameHealth = 3;
	TextureAsset* image = nullptr;
	glm::vec2 size = { 0,0 };

	std::function<int()> dataBinding = nullptr;
};

#endif


