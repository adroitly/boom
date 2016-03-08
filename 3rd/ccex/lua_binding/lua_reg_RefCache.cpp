/*
 The MIT License (MIT)

 Permission is hereby granted, free of charge, to any person obtaining a copy
 of this software and associated documentation files (the "Software"), to deal
 in the Software without restriction, including without limitation the rights
 to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 copies of the Software, and to permit persons to whom the Software is
 furnished to do so, subject to the following conditions:

 The above copyright notice and this permission notice shall be included in all
 copies or substantial portions of the Software.

 THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 SOFTWARE.
 */

#include "LuaBasicConversions.h"
#include "ccex/RefCache.h"
#include "cclua/cclua.hpp"

namespace ccex
{
    static int lua_RefCache_add(lua_State* L)
    {
        return cclua::obj_call(L,
                               [=](RefCache* cache, cclua::Index refIdx, const char* key)
                               {
                                   cocos2d::Ref* ref;
                                   luaval_to_object<cocos2d::Ref>(L, refIdx.val, "cc.Ref", &ref);
                                   if (ref)
                                   {
                                       cache->add(ref, key);
                                   }
                               });
    }

    static int lua_RefCache_remove(lua_State* L)
    {
        return cclua::obj_call(L,
                               [=](RefCache* cache, const char* key)
                               {
                                   cache->remove(key);
                               });
    }

    static int lua_RefCache_removeAll(lua_State* L)
    {
        return cclua::obj_call(L,
                               [=](RefCache* cache)
                               {
                                   cache->removeAll();
                               });
    }

    static int lua_RefCache_get(lua_State* L)
    {
        return cclua::obj_call(L,
                               [=](RefCache* cache, const char* key)
                               {
                                   auto ref = cache->get(key);
                                   object_to_luaval(L, "cc.Ref", ref);
                                   return cclua::NResults(1);
                               });
    }

    static int lua_RefCache_create(lua_State* L)
    {
        return cclua::obj_call(L,
                               [=](void* ctx)
                               {
                                   RefCache* ret = RefCache::create();
                                   object_to_luaval(L, "ccex.RefCache", ret);
                                   return cclua::NResults(1);
                               });
    }

    static int lua_RefCache_getInstance(lua_State* L)
    {
        return cclua::obj_call(L,
                               [=](void* ctx)
                               {
                                   RefCache* ret = RefCache::getInstance();
                                   object_to_luaval(L, "ccex.RefCache", ret);
                                   return cclua::NResults(1);
                               });
    }

    static int lua_RefSet_create(lua_State* L)
    {
        return cclua::obj_call(L,
                               [=](void* ctx)
                               {
                                   RefSet* ret = RefSet::create();
                                   object_to_luaval(L, "ccex.RefSet", ret);
                                   return cclua::NResults(1);
                               });
    }

    static int lua_RefSet_add(lua_State* L)
    {
        return cclua::obj_call(L,
                               [=](RefSet* refSet, cclua::Index refIdx)
                               {
                                   cocos2d::Ref* ref;
                                   luaval_to_object<cocos2d::Ref>(L, refIdx.val, "cc.Ref", &ref);
                                   if (ref)
                                   {
                                       refSet->add(ref);
                                   }
                               });
    }

    static int lua_RefSet_reuse(lua_State* L)
    {
        return cclua::obj_call(L,
                               [=](RefSet* refSet)
                               {
                                   auto ref = refSet->reuse();
                                   object_to_luaval(L, "cc.Ref", ref);
                                   return cclua::NResults(1);
                               });
    }

    int lua_reg_RefSet(lua_State* L)
    {
        cclua::ToLuaCClass<RefSet> cls(L, "RefSet", "ccex.RefSet", "cc.Ref");
        tolua_function(L, "create", lua_RefSet_create);
        tolua_function(L, "add", lua_RefSet_add);
        tolua_function(L, "reuse", lua_RefSet_reuse);
        return 1;
    }

    int lua_reg_RefCache(lua_State* L)
    {
        cclua::ToLuaCClass<RefCache> cls(L, "RefCache", "ccex.RefCache", "cc.Ref");

        tolua_function(L, "add", lua_RefCache_add);
        tolua_function(L, "remove", lua_RefCache_remove);
        tolua_function(L, "removeAll", lua_RefCache_removeAll);
        tolua_function(L, "get", lua_RefCache_get);
        tolua_function(L, "create", lua_RefCache_create);
        tolua_function(L, "getInstance", lua_RefCache_getInstance);

        return 1;
    }
}
