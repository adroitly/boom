//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_DEFINITIONMAP_H__
#define __FLA_DEFINITIONMAP_H__

#include <boost/container/flat_map.hpp>
#include <boost/call_traits.hpp>
#include "./fla_Definition.h"

namespace fla
{
    template <typename KeyT>
    class DefinitionMap final
    {
    public:
        typedef boost::container::flat_map<KeyT, Definition::Ptr> map_type;
        typedef typename boost::call_traits<KeyT>::param_type param_type;

        void setDefiniton(param_type Id, const Definition::Ptr& definition)
        {
            _definitions[Id] = definition;
        }
        
        void push_back(const Definition::Ptr& definition)
        {
            _definitions[definition->getId()] = definition;
        }

        typedef typename map_type::const_iterator const_iterator;

        const_iterator begin() const
        {
            return _definitions.begin();
        }

        const_iterator end() const
        {
            return _definitions.end();
        }
        
        size_t size() const
        {
            return _definitions.size();
        }

        Definition::Ptr findDefinition(param_type Id) const;
        void replaceDefinition(param_type ID, const Definition::Ptr& defintion);

    private:
        map_type _definitions;
    };

    template <typename KeyT>
    Definition::Ptr DefinitionMap<KeyT>::findDefinition(param_type Id) const
    {
        auto iter = _definitions.find(Id);
        if (iter != _definitions.end())
        {
            return iter->second;
        }
        return Definition::Ptr();
    }

    template <typename KeyT>
    void DefinitionMap<KeyT>::replaceDefinition(param_type ID, const Definition::Ptr& defintion)
    {
        auto iter = _definitions.find(ID);
        if (iter != _definitions.end())
        {
            iter->second = defintion;
        }
    }
}

#endif
