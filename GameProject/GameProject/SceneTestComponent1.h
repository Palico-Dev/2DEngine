#pragma once
#include "Component.h"

class SceneTestComponent1 :
    public Component
{
    DECLARE_DYNAMIC_DERIVED_CLASS(SceneTestComponent1, Component)

public:
    void Initialize() override;
    void Update() override;
};

class ZombieAIComponent :
    public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(ZombieAIComponent, Component)
public:
    //void Initialize() override;
	void OnComponentInitialized() override;
    void Update() override;

private:
	int StarvingTime = 0;
    float timer = 0.0f;
	float timeToSearch = 2.0f;
};

class ZombiePlayingComponent :
    public Component
{
    DECLARE_DYNAMIC_DERIVED_CLASS(ZombiePlayingComponent, Component)
public:
    void OnComponentInitialized() override;
    void Update() override;
private:
	float timer = 0.0f;
    float timeToSearch = 2.0f;
};

class ZombieFactoryComponent :
    public Component
{
    DECLARE_DYNAMIC_DERIVED_CLASS(ZombieFactoryComponent, Component)
public:
	void OnComponentInitialized() override;
    void Update() override;

private:
	float spawn_delay = 15.0f;
	float timer = 0.0f;
};

class AngelFactoryComponent:
    public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(AngelFactoryComponent, Component) 
public:
        void OnComponentInitialized() override;
        void Update() override;

private:
    float spawn_delay = 10.0f;
    float timer = 0.0f;
};

class AngelPlayingComponent :
    public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(AngelPlayingComponent, Component)
public:
    void Update() override;
	void OnComponentInitialized() override;
private:
    float timer = 0.0f;
};

class AngelAIComponent :
    public Component
{
    DECLARE_DYNAMIC_DERIVED_CLASS(AngelAIComponent, Component)
public:
    void OnComponentInitialized() override;
    void Update() override;
private:
    int MissHumansTime = 0;
    float timer = 0.0f;
    float timeToSearch = 3.0f;
};