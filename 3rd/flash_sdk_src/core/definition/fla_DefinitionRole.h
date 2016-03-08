//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_DEFINEROLE_H__
#define __FLA_DEFINEROLE_H__

#include <vector>
#include <cassert>
#include "fla_Definition.h"

namespace fla
{
    /*
     角色定义，一个角色有多个状态，另外有个默认的状态
     比如一个骑士，可能有 攻击，行走，跑步 等状态
     */
    class DefinitionRole : public DefinitionHelper<DefinitionRole>
    {
    public:
        void addState(const std::string& name, const Definition::Ptr& state);
        void changeStateName(const std::string& name, const Definition::Ptr& state);
        
        void setDefualtState(const std::string& name);

        Definition::Ptr findDefinition(const std::string& name) const;
        int findStateIndex(const std::string& name) const;

        Definition::Ptr defaultState() const;
        const std::string& defaultName() const;
        std::string stateName(const Definition::Ptr& state) const;
        virtual Rect getBounds() const override;

        // State的名字和Define的名字可以不同
        struct State
        {
        public:
            State(const std::string& n, const Definition::Ptr& s) : name(n), definition(s)
            {
            }
            std::string name;
            Definition::Ptr definition;
        };

        const std::vector<State>& getStates() const
        {
            return _states;
        }

        virtual void onFinishParse() override
        {
        }

    private:
        friend class DefinitionHelper<DefinitionRole>;
        DefinitionRole() : _defaultIndex(0)
        {
        }

    private:
        std::vector<State> _states;
        size_t _defaultIndex;
    };
}

#endif
