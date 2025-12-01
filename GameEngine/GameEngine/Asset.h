#pragma once

#ifndef _ASSET_H_
#define _ASSET_H_

#include "Object.h"

class Asset : public Object
{
	DECLARE_ABSTRACT_DERIVED_CLASS(Asset, Object)

private:
	friend class AssetManager;
	virtual void Load() = 0;
	virtual void Destroy() = 0;

protected:
	std::string type = "";
	std::string path = "";
	int refCount = 0;
};

#endif
