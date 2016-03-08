//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "../../core/base/fla_Base.h"
#if FLA_USE_LUA_BINDING == 1

#include "FlaSDK.h"
#include "tolua_fix.h"
#include "LuaBasicConversions.h"
#include "lua_cocos2dx_flashsdk.h"
#include "../../core/definition/fla_Definition.h"
#include "clover/ScopeGuard.h"
#include "cclua/cclua.hpp"
#include "cocos2d/LuaScriptHandlerMgr.h"
#include "CCLuaEngine.h"

namespace
{
    typedef enum
    {
        EVENT_MOVIE_NONE = (int)ScriptHandlerMgr::HandlerType::EVENT_CUSTOM_BEGAN + 1,
        EVENT_MOVIE_START,
        EVENT_MOVIE_FINISH,
        EVENT_MOVIE_STEP,
    } EventHandler;
}

static int lua_goToFrame(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](FlaMovieNode* node, int frame)
                           {
                               node->goToFrame(frame);
                           });
}

static int lua_getMovieName(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](FlaMovieNode* node)
                           {
                               return node->getMovieName();
                           });
}

static int lua_getMovieScale(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](FlaMovieNode* node)
                           {
                               return node->getMovieScale();
                           });
}

static int lua_getCurrentFrame(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](FlaMovieNode* node)
                           {
                               return node->getCurrentFrame();
                           });
}

static int lua_getCacheStrategy(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](FlaMovieNode* node)
                           {
                               FlaCacheStrategy* listener = node->getCacheStrategy();
                               if (listener)
                               {
                                   lua_pushlightuserdata(L, listener);
                               }
                               else
                               {
                                   lua_pushnil(L);
                               }
                               return cclua::NResults(1);
                           });
}

static int lua_getStateName(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](FlaMovieNode* node)
                           {
                               return node->getStateName();
                           });
}

static int lua_setColorTransform(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](FlaMovieNode* node, cclua::Index idx0, cclua::Index idx1)
                           {
                               float mult[4];
                               float add[4];

                               if (easy_lua::read_list(L, idx0.val, mult, 4) == 4 &&
                                   easy_lua::read_list(L, idx1.val, add, 4) == 4)
                               {
                                   node->setColorTransform(mult, add);
                               }
                           });
}

static int lua_changeState(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](FlaMovieNode* node, cclua::Index idx)
                           {
                               auto type = lua_type(L, idx.val);
                               if (type == LUA_TSTRING)
                               {
                                   const char* name = lua_tostring(L, idx.val);
                                   return node->changeState(name);
                               }
                               else if (type == LUA_TNUMBER)
                               {
                                   int stateIdx = (int)luaL_checkinteger(L, idx.val);
                                   return node->changeState(stateIdx);
                               }
                               return false;
                           });
}

static int lua_findMoviePart(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](FlaMovieNode* node, cclua::Index idx)
                           {
                               auto type = lua_type(L, idx.val);
                               FlaMoviePart part;
                               if (type == LUA_TSTRING)
                               {
                                   const char* name = lua_tostring(L, idx.val);
                                   part = node->findMoviePart(name);
                               }
                               else if (type == LUA_TNUMBER)
                               {
                                   int stateIdx = (int)luaL_checkinteger(L, idx.val);
                                   part = node->findMoviePart(stateIdx);
                               }

                               flalua::pushMoviePart(L, part);
                               return cclua::NResults(1);
                           });
}

static int lua_setBlurLevelClip(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](FlaMovieNode* node, bool flag, int level)
                           {
                               node->setBlurLevelClip(flag, level);
                           });
}

static int lua_setCacheStrategy(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](FlaMovieNode* node, cclua::Index idx)
                           {
                               if (lua_isnil(L, idx.val))
                               {
                                   node->setCacheStrategy(nullptr);
                               }
                               else
                               {
                                   auto strategy = (FlaCacheStrategy*)lua_touserdata(L, idx.val);
                                   node->setCacheStrategy(strategy);
                               }
                           });
}

static int lua_setGLProgram(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](FlaMovieNode* node, cclua::Index idx)
                           {
                               FlaGLProgram* program;
                               luaval_to_object(L, 2, "fla.GLProgram", &program);
                               if (program)
                               {
                                   node->setFlaGLProgram(program);
                               }

                           });
}

static int lua_stepFrame(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](FlaMovieNode* node)
                           {
                               node->stepFrame();
                           });
}

static int lua_getDefinition(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](FlaMovieNode* node)
                           {
                               FlaDefinition ret = node->getDefinition();
                               flalua::pushDefinition(L, ret);
                               return cclua::NResults(1);
                           });
}

static int lua_setAutoFlipY(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](FlaMovieNode* node, bool flag)
                           {
                               node->setAutoFlipY(flag);
                           });
}

template <typename T>
static int s_movieNode_createWithDefinition(lua_State* L, const char* name)
{
    int argc = lua_gettop(L) - 1;
    if (argc == 2 || argc == 1)
    {
        fla::Definition* definition;
        if (!luaval_to_object<fla::Definition>(L, 2, "fla.Definition", &definition))
        {
            return 0;
        }

        float scale = 1.0;
        if (argc == 2)
        {
            scale = luaL_checknumber(L, 3);
        }

        auto ret = T::createWithDefinition(FlaDefinition(definition), scale);
        object_to_luaval(L, name, ret);
        return 1;
    }
    return 0;
}

static int lua_createWithDefinition(lua_State* L)
{
    return s_movieNode_createWithDefinition<FlaMovieNode>(L, "fla.MovieNode");
}

static void s_handleEvent(FlaMovieNode* self, ScriptHandlerMgr::HandlerType type, FlaMovieNode* node)
{
    int handler = ScriptHandlerMgr::getInstance()->getObjectHandler(self, type);
    assert(handler != 0);
    LuaStack* stack = LuaEngine::getInstance()->getLuaStack();
    stack->pushObject(node, "fla.MovieNode");
    stack->executeFunctionByHandler(handler, 1);
}

static EventHandler s_parseEventType(const std::string& typestr)
{
    if (typestr == "start")
    {
        return EVENT_MOVIE_START;
    }
    else if (typestr == "finish")
    {
        return EVENT_MOVIE_FINISH;
    }
    else if (typestr == "step")
    {
        return EVENT_MOVIE_STEP;
    }
    return EVENT_MOVIE_NONE;
}

static int lua_handleMovieEvent(lua_State* L)
{
    auto self = (FlaMovieNode*)tolua_tousertype(L, 1, 0);
    int argc = lua_gettop(L) - 1;

    if (argc == 2)
    {
        const char* typestr = luaL_checkstring(L, 2);
        auto type_tmp = s_parseEventType(typestr);
        if (type_tmp == EVENT_MOVIE_NONE)
        {
            return 0;
        }

        ScriptHandlerMgr::HandlerType type = (ScriptHandlerMgr::HandlerType)(int)type_tmp;
        LUA_FUNCTION handler = toluafix_ref_function(L, 3, 0);
        std::function<void(FlaMovieNode*)>* callback = nullptr;

        switch ((int)type)
        {
            case EVENT_MOVIE_START:
                callback = &self->onMovieStart;
                break;

            case EVENT_MOVIE_FINISH:
                callback = &self->onMovieFinish;
                break;

            case EVENT_MOVIE_STEP:
                callback = &self->onMovieStepFrame;
                break;

            default:
                break;
        }

        assert(callback);
        if (0 == handler)
        {
            ScriptHandlerMgr::getInstance()->removeObjectHandler((void*)self, type);
            *callback = std::function<void(FlaMovieNode*)>();
        }
        else
        {
            ScriptHandlerMgr::getInstance()->addObjectHandler((void*)self, handler, type);
            *callback = std::bind(s_handleEvent, self, type, std::placeholders::_1);
        }
    }
    return 0;
}

int lua_register_fla_MovieNode(lua_State* L)
{
    cclua::ToLuaCClass<FlaMovieNode> cls(L, "MovieNode", "fla.MovieNode", "cc.Node");

    tolua_function(L, "goToFrame", lua_goToFrame);
    tolua_function(L, "getCurrentFrame", lua_getCurrentFrame);
    tolua_function(L, "getMovieName", lua_getMovieName);
    tolua_function(L, "getMovieScale", lua_getMovieScale);
    tolua_function(L, "changeState", lua_changeState);
    tolua_function(L, "setColorTransform", lua_setColorTransform);
    tolua_function(L, "setCacheStrategy", lua_setCacheStrategy);
    tolua_function(L, "getCacheStrategy", lua_getCacheStrategy);
    tolua_function(L, "getStateName", lua_getStateName);
    tolua_function(L, "setFlaGLProgram", lua_setGLProgram);
    tolua_function(L, "stepFrame", lua_stepFrame);
    tolua_function(L, "getDefinition", lua_getDefinition);
    tolua_function(L, "createWithDefinition", lua_createWithDefinition);
    tolua_function(L, "setAutoFlipY", lua_setAutoFlipY);
    tolua_function(L, "handleMovieEvent", lua_handleMovieEvent);
    tolua_function(L, "setBlurLevelClip", lua_setBlurLevelClip);
    tolua_function(L, "findMoviePart", lua_findMoviePart);
    return 1;
}

static int lua_time_update(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](FlaTimeMovieNode* node, float t)
                           {
                               node->time_update(t);
                           });
}

static int lua_time_createWithDefinition(lua_State* L)
{
    return s_movieNode_createWithDefinition<FlaTimeMovieNode>(L, "fla.TimeMovieNode");
}

static int lua_time_setEnableRatio(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](FlaTimeMovieNode* node, bool flag)
                           {
                               node->time_setEnableRatio(flag);
                           });
}

static int lua_time_setFrameRate(lua_State* L)
{
    return cclua::obj_call(L,
                           [=](FlaTimeMovieNode* node, float frameRate)
                           {
                               node->time_setFrameRate(frameRate);
                           });
}

int lua_register_fla_TimeMovieNode(lua_State* L)
{
    cclua::ToLuaCClass<FlaTimeMovieNode> cls(L, "TimeMovieNode", "fla.TimeMovieNode", "fla.MovieNode");
    tolua_function(L, "createWithDefinition", lua_time_createWithDefinition);
    tolua_function(L, "time_update", lua_time_update);
    tolua_function(L, "time_setEnableRatio", lua_time_setEnableRatio);
    tolua_function(L, "time_setFrameRate", lua_time_setFrameRate);
    return 1;
}

#endif
