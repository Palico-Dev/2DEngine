#pragma once
#ifndef ZOMBIEFACTORY_H
#define ZOMBIEFACTORY_H

#include "Component.h"

/// <summary>
/// 
/// </summary>
class ZombieFactory : public Component
{
    DECLARE_DYNAMIC_DERIVED_CLASS(ZombieFactory, Component)

public:
    ~ZombieFactory() override {}
    
    /// <summary>
    /// 
    /// </summary>
    void Initialize() override;
    
    /// <summary>
    /// 
    /// </summary>
    void Update() override;

private:
    float spawn_delay = 1.0f;
    float current_spawn_delay = 0.0f;
};

#endif // !ZOMBIEFACTORY_H