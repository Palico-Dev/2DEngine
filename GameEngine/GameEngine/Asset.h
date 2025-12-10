#pragma once

#ifndef _ASSET_H_
#define _ASSET_H_

#include "Object.h"
#include "FileManager.h"

class Asset : public Object
{
	DECLARE_ABSTRACT_DERIVED_CLASS(Asset, Object)

public:
	std::string& GetFileName() { return fileName; }

private:
	friend class AssetManager;
	virtual void Load(json::JSON j, std::string& _fileName) = 0;
	virtual void Destroy() = 0;

protected:
	int refCount = 0;
	std::string fileName = "";
};

#endif
