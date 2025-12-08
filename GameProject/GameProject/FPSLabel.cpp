#include "GameCore.h"
#include "FPSLabel.h"
IMPLEMENT_DYNAMIC_CLASS(FPSLabel)

void FPSLabel::Update()
{
	timer += EngineTime->DeltaTime();
	if (timer > 1.0f)
	{
		std::string fps = std::to_string(EngineTime->FPS());
		SetText(fps);
	}
	
	Widget::Update();
}

void FPSLabel::Start()
{
	Debug::Log("FPS Label Start");
	EngineTime = &Time::Instance();
}
