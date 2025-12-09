#pragma once
#ifndef _DATABINDINGREGISTRY_H_
#define _DATABINDINGREGISTRY_H_

class DataBindingRegistry
{
	DECLARE_SINGLETON(DataBindingRegistry);

public:
	using StringBinder = std::function<std::string()>;
	using FloatBinder = std::function<float()>;
	using IntBinder = std::function<int()>;


	void RegisterString(const STRCODE key, StringBinder binder)
	{
		stringBindings[key] = binder;
	}

	void RegisterFloat(const STRCODE key, FloatBinder binder)
	{
		floatBindings[key] = binder;
	}

	void RegisterInt(const STRCODE key, IntBinder binder)
	{
		intBindings[key] = binder;
	}


	StringBinder GetStringBinding(const STRCODE key)
	{
		if (stringBindings.find(key) != stringBindings.end())
		{
			return stringBindings[key];
		}
		Debug::Warning("String Binding not found:" + key);
		return nullptr;
	}

	FloatBinder GetFloatBinding(const STRCODE key)
	{
		if (floatBindings.find(key) != floatBindings.end())
		{
			return floatBindings[key];
		}
		Debug::Warning("Float Binding not found:" + key);
		return nullptr;
	}

	IntBinder GetIntBinding(const STRCODE key)
	{
		if (intBindings.find(key) != intBindings.end())
		{
			return intBindings[key];
		}
		Debug::Warning("Int Binding not found:" + key);
		return nullptr;
	}


private:
	std::unordered_map<STRCODE, StringBinder> stringBindings;
	std::unordered_map<STRCODE, FloatBinder>  floatBindings;
	std::unordered_map<STRCODE, IntBinder>    intBindings;
};

#endif


