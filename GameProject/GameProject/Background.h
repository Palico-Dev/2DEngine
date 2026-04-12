#pragma once
#ifndef _BACKGROUND_H_
#define _BACKGROUND_H_

#include "Component.h"

class PrefabAsset;

class Background : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(Background,Component)

private:
	void Update() override;
	void Load(json::JSON& jsonData) override;

	void CreateNebula();
	void CreateSpeedline();
	void CreateStar();

private:
	std::string starSmallName = "";
	std::string starBigName = "";
	std::string nebulaName = "";
	std::string speedlineName = "";
	PrefabAsset* starSmall = nullptr;
	PrefabAsset* starBig = nullptr;
	PrefabAsset* nebula = nullptr;
	PrefabAsset* speedline = nullptr;

	float nebulaTimer = 3.0f;
	float speedlineTimer = 1.0f;
	float starTimer = 0.0f;

protected:
	bool IsServerOnly() const override
	{
		return true;
	}

};

#endif


