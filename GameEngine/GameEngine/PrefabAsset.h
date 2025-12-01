#ifndef _PREFABASSET_H_
#define _PREFABASSET_H_

#include "Asset.h"

class Entity;

class PrefabAsset : public Asset
{
    DECLARE_DYNAMIC_DERIVED_CLASS(PrefabAsset, Asset)

public:
    Entity* GetPrefabBlueprintEntity() { return m_Entity; }

private:
    Entity* m_Entity;
    void Load() override;
    void Destroy() override;
};

#endif
