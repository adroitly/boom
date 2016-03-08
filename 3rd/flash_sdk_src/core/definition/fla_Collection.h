//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_COLLECTION_H__
#define __FLA_COLLECTION_H__

#include "./fla_Definition.h"
#include "../base/fla_Ref.h"
#include "./fla_DefinitionMap.h"

namespace fla
{
    class Collection : public Ref<Collection>
    {
    public:
        static Collection::Ptr create(const std::map<int, Definition::Ptr>& dict, float frameRate, int rootId);

        Definition::Ptr findDefinition(const std::string& name) const;
        Definition::Ptr findDefinition(int ID) const;
        Definition::Ptr rootDefinition() const;

        float getFrameRate() const
        {
            return _frameRate;
        }

        typedef std::function<void(const Definition::Ptr& def)> WalkFunType;
        void walk(const WalkFunType& fun) const;
        void walk(DefinitionType movieType, const WalkFunType& fun) const;

        void walkName(const WalkFunType& fun) const;

    private:
        Collection(const std::map<int, Definition::Ptr>& dict, float frameRate, int rootId);
        Collection();
        float _frameRate;
        int _rootId;
        DefinitionMap<int> _IdMap;
        DefinitionMap<std::string> _nameMap;
    };
}

#endif
