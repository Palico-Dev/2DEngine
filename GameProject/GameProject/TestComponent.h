#pragma once
#ifndef TESTCOMPONENT_H
#define TESTCOMPONENT_H

#include "Component.h"

/// <summary>
/// TestComponent1 Class
/// This class does nothing and is here so there can be multiple TestClasses
/// </summary>
class TestComponent1 : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(TestComponent1, Component)

public:
	TestComponent1() {}
	~TestComponent1() override {}
	void Initialize() override {}
	void Update() override {}
};

/// <summary>
/// TestComponent2 Class
/// This class does nothing and is here so there can be multiple TestClasses
/// </summary>
class TestComponent2 : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(TestComponent2, Component)

public:
	TestComponent2() {}
	~TestComponent2() override {}
	void Initialize() override {}
	void Update() override {}
};

/// <summary>
/// TestComponent2 Class
/// This class does nothing and is here so there can be multiple TestClasses
/// </summary>
class TestComponent3 : public Component
{
	DECLARE_DYNAMIC_DERIVED_CLASS(TestComponent3, Component)

public:
	TestComponent3() {}
	~TestComponent3() override {}
	void Initialize() override {}
	void Update() override {}
};

#endif // !TESTCOMPONENT_H