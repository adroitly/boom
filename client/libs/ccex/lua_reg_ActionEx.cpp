//
//  lua_reg_ActionEx.cpp
//  big-devil
//
//  Created by PatGame on 15/6/3.
//
//

#include "lua_reg_ActionEx.h"
#include "LuaBasicConversions.h"
#include "cclua/cclua.hpp"
#include "ActionEx.h"
#include "CCLuaValue.h"
#include "CCLuaEngine.h"

namespace ccex
{
    static cclua::NResults lua_pushActionGroup(lua_State* L, ActionGroup* g)
    {
        object_to_luaval<ActionGroup>(L, "ccex.ActionGroup", g);
        return cclua::NResults(1);
    }
    
    // ActionGroup
    int lua_ActionGroup_moveTo(lua_State* L)
    {
        return cclua::obj_call(L,
                               [=](ActionGroup* g, float time, cclua::Index refIdx)
                               {
                                   cocos2d::Vec2 pos;
                                   luaval_to_vec2(L, refIdx.val, &pos, "ActionGroup.moveTo");
                                   g->moveTo(time, pos);
                                   return lua_pushActionGroup(L, g);
                               });
    }

    int lua_ActionGroup_scaleTo(lua_State* L)
    {
        return cclua::obj_call(L,
                               [=](ActionGroup* g, float time, float s)
                               {
                                   g->scaleTo(time, s);
                                   return lua_pushActionGroup(L, g);
                               });
    }

    int lua_ActionGroup_fadeTo(lua_State* L)
    {
        return cclua::obj_call(L,
                               [=](ActionGroup* g, float time, float o)
                               {
                                   g->fadeTo(time, o);
                                   return lua_pushActionGroup(L, g);
                               });
    }

    int lua_ActionGroup_fadeOut(lua_State* L)
    {
        return cclua::obj_call(L,
                               [=](ActionGroup* g, float time)
                               {
                                   g->fadeOut(time);
                                   return lua_pushActionGroup(L, g);
                               });
    }

    int lua_ActionGroup_delayTime(lua_State* L)
    {
        return cclua::obj_call(L,
                               [=](ActionGroup* g, float time)
                               {
                                   g->delayTime(time);
                                   return lua_pushActionGroup(L, g);
                               });
    }

    int lua_ActionGroup_moveBy(lua_State* L)
    {
        return cclua::obj_call(L,
                               [=](ActionGroup* g, float time, cclua::Index refIdx)
                               {
                                   cocos2d::Vec2 pos;
                                   luaval_to_vec2(L, refIdx.val, &pos, "ActionGroup.moveBy");
                                   g->moveBy(time, pos);
                                   return lua_pushActionGroup(L, g);
                               });
    }

    int lua_ActionGroup_callFunc(lua_State* L)
    {
        return cclua::obj_call(L,
                               [=](ActionGroup* g, cclua::Index refIdx)
                               {
                                   LUA_FUNCTION handler = toluafix_ref_function(L, refIdx.val, 0);
                                   auto mgr = ScriptHandlerMgr::getInstance();
                                   auto type = (ScriptHandlerMgr::HandlerType)(
                                       (int)ScriptHandlerMgr::HandlerType::CALLFUNC + g->numberOfCallFunc());

                                   if (0 == mgr->getObjectHandler(g, type))
                                   {
                                       mgr->addObjectHandler(g, handler, type);
                                       
                                       auto func = [=]()
                                       {
                                           LUA_FUNCTION handler = mgr->getObjectHandler(g, type);
                                           if (0 != handler)
                                           {
                                               LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
                                               stack->executeFunctionByHandler(handler, 0);
                                           }
                                       };
                                       g->callFunc(func);
                                   }
                                   return lua_pushActionGroup(L, g);
                               });
    }
    
    int lua_ActionGroup_action(lua_State*L)
    {
        return cclua::obj_call(L,
                               [=](ActionGroup* g, cclua::Index refIdx)
                               {
                                   cocos2d::FiniteTimeAction* action;
                                   luaval_to_object<cocos2d::FiniteTimeAction>(L, refIdx.val, "cc.FiniteTimeAction", &action);
                                   g->action(action);
                                   return lua_pushActionGroup(L, g);
                               });
    }

    int lua_ActionGroup_run(lua_State* L)
    {
        return cclua::obj_call(L,
                               [=](ActionGroup* g, cclua::Index refIdx)
                               {
                                   cocos2d::Node* node;
                                   luaval_to_object<cocos2d::Node>(L, refIdx.val, "cc.Node", &node);
                                   g->run(node);
                               });
    }

    int lua_reg_ActionGroup(lua_State* L)
    {
        cclua::ToLuaCClass<Spawn> cls(L, "ActionGroup", "ccex.ActionGroup", "cc.ActionInterval");

        tolua_function(L, "moveTo", lua_ActionGroup_moveTo);
        tolua_function(L, "moveBy", lua_ActionGroup_moveBy);
        tolua_function(L, "scaleTo", lua_ActionGroup_scaleTo);
        tolua_function(L, "callFunc", lua_ActionGroup_callFunc);
        tolua_function(L, "delayTime", lua_ActionGroup_delayTime);
        tolua_function(L, "fadeTo", lua_ActionGroup_fadeTo);
        tolua_function(L, "fadeOut", lua_ActionGroup_fadeOut);
        tolua_function(L, "action", lua_ActionGroup_action);
        tolua_function(L, "run", lua_ActionGroup_run);
        return 1;
    }

    // Sequence
    static int lua_Sequence_create(lua_State* L)
    {
        return cclua::obj_call(L,
                               [=](void* ctx)
                               {
                                   Sequence* ret = Sequence::create();
                                   object_to_luaval(L, "ccex.SequenceEx", ret);
                                   return cclua::NResults(1);
                               });
    }

    int lua_reg_Sequence(lua_State* L)
    {
        cclua::ToLuaCClass<Sequence> cls(L, "SequenceEx", "ccex.SequenceEx", "ccex.ActionGroup");
        tolua_function(L, "create", lua_Sequence_create);
        return 1;
    }
    
    // Spawn
    static int lua_Spawn_create(lua_State* L)
    {
        return cclua::obj_call(L,
                               [=](void* ctx)
                               {
                                   Spawn* ret = Spawn::create();
                                   object_to_luaval(L, "ccex.SpawnEx", ret);
                                   return cclua::NResults(1);
                               });
    }
    
    int lua_reg_Spawn(lua_State* L)
    {
        cclua::ToLuaCClass<Spawn> cls(L, "SpawnEx", "ccex.SpawnEx", "ccex.ActionGroup");
        tolua_function(L, "create", lua_Spawn_create);
        return 1;
    }


    // lua_reg
    int lua_reg_ActionEx(lua_State* L)
    {
        tolua_open(L);
        tolua_module(L, "ccex", 0);
        tolua_beginmodule(L, "ccex");

        lua_reg_ActionGroup(L);
        lua_reg_Sequence(L);
        lua_reg_Spawn(L);
        
        tolua_endmodule(L);

        return 1;
    }
}