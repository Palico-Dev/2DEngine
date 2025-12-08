#pragma once
#ifndef _FPSLABEL_H_
#define _FPSLABEL_H_

#include "UILabel.h"
#include "EngineTime.h"

class FPSLabel : public UILabel
{
	DECLARE_DYNAMIC_DERIVED_CLASS(FPSLabel,UILabel)
	
private:
	void Update() override;
	void Start() override;

private:
	Time* EngineTime;
	float timer = 0.0f;
};

#endif


