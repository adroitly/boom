//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_DefinitionRole.h"

namespace fla
{
    Definition::Ptr DefinitionRole::findDefinition(const std::string& name) const
    {
        for (auto& state : _states)
        {
            if (state.name == name)
            {
                return state.definition;
            }
        }
        return Definition::Ptr();
    }

    int DefinitionRole::findStateIndex(const std::string& name) const
    {
        for (size_t idx = 0; idx < _states.size(); idx++)
        {
            if (_states[idx].name == name)
            {
                return (int)idx;
            }
        }
        return -1;
    }

    void DefinitionRole::setDefualtState(const std::string& name)
    {
        for (size_t i = 0; i < _states.size(); i++)
        {
            if (_states[i].name == name)
            {
                _defaultIndex = i;
                break;
            }
        }
    }

    const std::string& DefinitionRole::defaultName() const
    {
        return _states[_defaultIndex].name;
    }

    Definition::Ptr DefinitionRole::defaultState() const
    {
        assert((size_t)_defaultIndex < _states.size());
        return _states[_defaultIndex].definition;
    }

    std::string DefinitionRole::stateName(const Definition::Ptr& definition) const
    {
        for (auto& state : _states)
        {
            if (state.definition == definition)
            {
                return state.name;
            }
        }
        return "";
    }

    void DefinitionRole::addState(const std::string& name, const Definition::Ptr& sprite)
    {
        _states.push_back(State(name, sprite));
    }

    void DefinitionRole::changeStateName(const std::string& name, const Definition::Ptr& state)
    {
        for (auto& s : _states)
        {
            if (s.definition == state)
            {
                s.name = name;
                return;
            }
        }
    }

    Rect DefinitionRole::getBounds() const
    {
        return defaultState()->getBounds();
    }
}
