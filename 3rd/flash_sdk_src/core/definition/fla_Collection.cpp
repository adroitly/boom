//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_Collection.h"
#include "libra/libra_string.h"

namespace fla
{
    Collection::Collection(const std::map<int, fla::Definition::Ptr>& dict, float frameRate, int rootId)
    {
        _rootId = rootId;
        _frameRate = frameRate;
        for (auto& def : dict)
        {
            auto name = def.second->getName();
            if (!str_is_empty(name))
            {
                _nameMap.setDefiniton(def.second->getName(), def.second);
            }
            _IdMap.setDefiniton(def.first, def.second);
        }
    }

    Collection::Collection()
    {
    }

    Collection::Ptr Collection::create(const std::map<int, fla::Definition::Ptr>& dict, float frameRate, int rootId)
    {
        return Collection::Ptr(new Collection(dict, frameRate, rootId), false);
    }

    Definition::Ptr Collection::findDefinition(const std::string& name) const
    {
        return _nameMap.findDefinition(name);
    }

    Definition::Ptr Collection::findDefinition(int ID) const
    {
        return _IdMap.findDefinition(ID);
    }

    Definition::Ptr Collection::rootDefinition() const
    {
        return findDefinition(_rootId);
    }

    void Collection::walk(const WalkFunType& fun) const
    {
        for (auto& iter : _IdMap)
        {
            fun(iter.second);
        }
    }

    void Collection::walk(DefinitionType movieType, const WalkFunType& fun) const
    {
        for (auto& iter : _IdMap)
        {
            if (iter.second->getType() == movieType)
            {
                fun(iter.second);
            }
        }
    }

    void Collection::walkName(const WalkFunType& fun) const
    {
        for (auto& iter : _nameMap)
        {
            fun(iter.second);
        }
    }
}