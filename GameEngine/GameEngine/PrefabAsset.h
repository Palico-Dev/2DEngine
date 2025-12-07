#ifndef _PREFABASSET_H_
#define _PREFABASSET_H_

#include "Asset.h"

class Entity;

class PrefabAsset : public Asset
{
    DECLARE_DYNAMIC_DERIVED_CLASS(PrefabAsset, Asset)

public:
    Entity* GetPrefab() { return prefab; }

private:
    Entity* prefab;
    void Load(json::JSON j) override;
    void Destroy() override;
};

#endif
