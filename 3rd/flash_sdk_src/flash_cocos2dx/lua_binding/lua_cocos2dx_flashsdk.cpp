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
#include "lua_cocos2dx_flashsdk.h"
#include "../../core/definition/fla_Collection.h"
#include "../src/fla_MoviePart.h"
#include "LuaBasicConversions.h"
#include "clover/ScopeGuard.h"

int lua_register_fla_MovieNode(lua_State* L);
int lua_register_fla_Definition(lua_State* L);
int lua_register_fla_Collection(lua_State* L);
int lua_register_fla_TimeMovieNode(lua_State* L);
int lua_register_fla_MoviePart(lua_State* L);

static int lua_register_fla_PixelFormat(lua_State* L)
{
    // Handler
    tolua_module(L, "PixelFormat", 0);
    tolua_beginmodule(L, "PixelFormat");
    CLOVER_SCOPE_EXIT
    {
        tolua_endmodule(L);
    };
    
    tolua_constant(L, "RGBA8888", (int)FlaPixelFormat::RGBA8888);
    tolua_constant(L, "RGBA4444", (int)FlaPixelFormat::RGBA4444);
    
    return 1;
}

static int lua_setTextureContentScaleFactor(lua_State* L)
{
    lua_Number scale = luaL_checknumber(L, 1);
    FlaSDK::setTextureContentScaleFactor(scale);
    return 0;
}

static int lua_purgeCachedData(lua_State* L)
{
    FlaSDK::purgeCachedData();
    return 0;
}

int register_all_cocos2dx_flasdk(lua_State* L)
{
    tolua_open(L);
    
    tolua_module(L, "fla", 0);
    tolua_beginmodule(L, "fla");
    CLOVER_SCOPE_EXIT
    {
        tolua_endmodule(L);
    };
    
    lua_register_fla_Collection(L);
    lua_register_fla_PixelFormat(L);
    lua_register_fla_Definition(L);
    lua_register_fla_MovieNode(L);
    lua_register_fla_TimeMovieNode(L);
    lua_register_fla_MoviePart(L);
    tolua_function(L, "setTextureContentScaleFactor", lua_setTextureContentScaleFactor);
    tolua_function(L, "purgeCachedData", lua_purgeCachedData);
    
    return 1;
}

namespace flalua
{
    void pushCollection(lua_State* L, const FlaCollection& collection)
    {
        if (collection.isNull())
        {
            lua_pushnil(L);
        }
        else
        {
            auto ptr = collection.getRaw();
            ptr->retain();
            ptr->autorelease();
            object_to_luaval(L, "fla.Collection", ptr);
        }
    }
    
    FlaCollection toCollection(lua_State* L, int idx)
    {
        auto cobj = (fla::Collection*)tolua_tousertype(L, idx, 0);
        return FlaCollection(cobj);
    }
    
    FlaDefinition toDefinition(lua_State* L, int idx)
    {
        auto cobj = (fla::Definition*)tolua_tousertype(L, idx, 0);
        return FlaDefinition(cobj);
    }
    
    static void s_pushDefinition(lua_State* L, fla::Definition* ptr)
    {
        if (ptr)
        {
            ptr->retain();
            ptr->autorelease();
            object_to_luaval<fla::Definition>(L, "fla.Definition", ptr);
        }
        else
        {
            lua_pushnil(L);
        }
    }
    
    void pushMoviePart(lua_State* L, const FlaMoviePart& part)
    {
        if (part.isNull())
        {
            lua_pushnil(L);
        }
        else
        {
            auto ptr = part.getRaw();
            ptr->retain();
            ptr->autorelease();
            object_to_luaval(L, "fla.MoviePart", ptr);
        }
    }
    
    void pushDefinition(lua_State* L, const FlaDefinition& defintion)
    {
        if (defintion.isNull())
        {
            lua_pushnil(L);
        }
        else
        {
            auto impl = defintion.getRaw();
            s_pushDefinition(L, impl);
        }
    }
    
    void pushDefinition(lua_State* L, const fla::Definition::Ptr& defintion)
    {
        s_pushDefinition(L, defintion.get());
    }
}

#endif
