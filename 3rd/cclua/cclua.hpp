/*
 The MIT License (MIT)

 Copyright (c) 2015 HJC hjcapple@gmail.com

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

#ifndef __CCLUA_H__
#define __CCLUA_H__

#include <string>
#include "tolua++.h"
#include "meta/Traits.h"
#include "meta/TypeManip.h"
#include "LuaBasicConversions.h"
#include "easy_lua/easy_lua.h"

namespace cclua
{
    typedef easy_lua::NResults NResults;
    typedef easy_lua::Index Index;

    // 返回值不为 void
    template <typename Fun, typename... Args>
    inline int __obj_call(lua_State* L, Fun&& fun, meta::false_type, Args... args)
    {
        auto result = fun(args...);
        return easy_lua::result_value(L, result);
    }

    // 返回值为 void
    template <typename Fun, typename... Args>
    inline int __obj_call(lua_State* L, Fun&& fun, meta::true_type, Args... args)
    {
        fun(args...);
        return 0;
    }

    template <int N, typename check_void>
    struct ObjCall;

    template <typename check_void>
    struct ObjCall<0, check_void>
    {
        template <typename Fun, typename Obj>
        static int call(lua_State* L, Fun&& fun, Obj* obj)
        {
            return __obj_call(L, std::forward<Fun>(fun), check_void(), obj);
        }
    };

    template <typename check_void>
    struct ObjCall<1, check_void>
    {
        template <typename Fun, typename Obj>
        static int call(lua_State* L, Fun&& fun, Obj* obj)
        {
            typedef typename meta::function_traits<Fun>::template arg<1>::type arg0_type;
            auto arg0 = easy_lua::check<arg0_type>(L, 2);
            return __obj_call(L, std::forward<Fun>(fun), check_void(), obj, arg0);
        }
    };

    template <typename check_void>
    struct ObjCall<2, check_void>
    {
        template <typename Fun, typename Obj>
        static int call(lua_State* L, Fun&& fun, Obj* obj)
        {
            typedef typename meta::function_traits<Fun>::template arg<1>::type arg0_type;
            typedef typename meta::function_traits<Fun>::template arg<2>::type arg1_type;

            auto arg0 = easy_lua::check<arg0_type>(L, 2);
            auto arg1 = easy_lua::check<arg1_type>(L, 3);
            return __obj_call(L, std::forward<Fun>(fun), check_void(), obj, arg0, arg1);
        }
    };

    template <typename Fun>
    int obj_call(lua_State* L, Fun&& fun)
    {
        typedef typename meta::function_traits<Fun>::template arg<0>::type ptr_type;
        typedef typename meta::function_traits<Fun>::result_type result_type;
        typedef typename meta::check<std::is_same<result_type, void>::value> check_void;

        const int N = meta::function_traits<Fun>::nargs - 1;
        auto obj = (ptr_type)tolua_tousertype(L, 1, 0);
        int argc = lua_gettop(L) - 1;
        if (argc == N)
        {
            return ObjCall<N, check_void>::call(L, std::forward<Fun>(fun), obj);
        }
        return 0;
    }

    template <typename T>
    class ToLuaCClass final
    {
    public:
        ToLuaCClass(lua_State* L, const char* module, const char* clsName, const char* baseName)
        {
            _LuaState = L;
            _module = module;
            _clsName = clsName;
            _baseName = baseName;

            tolua_usertype(L, clsName);
            tolua_cclass(L, module, clsName, baseName, NULL);

            tolua_beginmodule(L, module);
        }

        ~ToLuaCClass()
        {
            tolua_endmodule(_LuaState);

            std::string typeName = typeid(T).name();
            g_luaType[typeName] = _clsName;
            g_typeCast[_module] = _clsName;
        }

    private:
        lua_State* _LuaState;
        const char* _module;
        const char* _clsName;
        const char* _baseName;
    };
}

#endif
