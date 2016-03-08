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

#ifndef __EASY_LUA_H__
#define __EASY_LUA_H__

#include <string>
#include <algorithm>
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

#if LUA_VERSION_NUM == 501
#define lua_rawlen lua_objlen
//int lua_absindex(lua_State* L, int idx);
#endif

namespace easy_lua
{
    struct Index
    {
        explicit Index(int n) : val(n)
        {
        }
        int val;
    };

    struct NResults
    {
        explicit NResults(int n) : val(n)
        {
        }
        int val;
    };

    namespace detail
    {
        template <typename T>
        struct Type2Type
        {
            typedef T type;
        };

        inline Index read(lua_State* L, int idx, detail::Type2Type<Index>)
        {
            return Index(idx);
        }

        inline int read(lua_State* L, int idx, detail::Type2Type<int>)
        {
            return (int)lua_tointeger(L, idx);
        }

        inline bool read(lua_State* L, int idx, detail::Type2Type<bool>)
        {
            return lua_toboolean(L, idx);
        }

        inline float read(lua_State* L, int idx, detail::Type2Type<float>)
        {
            return lua_tonumber(L, idx);
        }

        inline const char* read(lua_State* L, int idx, detail::Type2Type<const char*>)
        {
            return lua_tostring(L, idx);
        }

        inline Index check(lua_State* L, int idx, detail::Type2Type<Index>)
        {
            return Index(idx);
        }

        inline int check(lua_State* L, int idx, detail::Type2Type<int>)
        {
            return (int)luaL_checkinteger(L, idx);
        }

        inline bool check(lua_State* L, int idx, detail::Type2Type<bool>)
        {
            return lua_toboolean(L, idx);
        }

        inline float check(lua_State* L, int idx, detail::Type2Type<float>)
        {
            return luaL_checknumber(L, idx);
        }

        inline const char* check(lua_State* L, int idx, detail::Type2Type<const char*>)
        {
            return luaL_checkstring(L, idx);
        }
    }

    void getfield_ex(lua_State* L, int idx, const char* k);
    void getfield_ex(lua_State* L, int idx, const std::string& k);
    void push_globals(lua_State* L);

    void print_stack(lua_State* L);

    bool safe_call(lua_State* L, int narg, int nres);

    template <typename T>
    inline T read(lua_State* L, int idx)
    {
        return detail::read(L, idx, detail::Type2Type<T>());
    }

    template <typename T>
    inline T check(lua_State* L, int idx)
    {
        return detail::check(L, idx, detail::Type2Type<T>());
    }

    inline void push(lua_State* L, int val)
    {
        lua_pushinteger(L, val);
    }

    inline void push(lua_State* L, bool val)
    {
        lua_pushboolean(L, val);
    }

    inline void push(lua_State* L, float val)
    {
        lua_pushnumber(L, val);
    }

    inline void push(lua_State* L, const std::string& str)
    {
        lua_pushlstring(L, str.c_str(), str.size());
    }

    inline void push(lua_State* L, const char* str)
    {
        lua_pushstring(L, str);
    }

    inline int result_value(lua_State* L, NResults n)
    {
        return n.val;
    }

    template <typename T>
    inline int result_value(lua_State* L, T&& val)
    {
        easy_lua::push(L, std::forward<T>(val));
        return 1;
    }

    template <typename Fun>
    void table_walk(lua_State* L, int idx, Fun&& fun)
    {
        lua_pushvalue(L, idx);
        lua_pushnil(L);
        while (lua_next(L, -2))
        {
            int top = lua_gettop(L);
            fun(top - 1, top);
            lua_pop(L, 1);
        }
        lua_pop(L, 1);
    }

    template <typename T>
    size_t read_list(lua_State* L, int idx, T* values, size_t n)
    {
        size_t len = lua_rawlen(L, idx);
        if (values == nullptr)
        {
            return len;
        }
        n = std::min(len, n);
        for (int i = 1; i <= n; i++)
        {
            lua_rawgeti(L, idx, i);
            values[i - 1] = read<T>(L, -1);
            lua_pop(L, 1);
        }
        return n;
    }

    int table_maxn(lua_State* L, int idx);
//    void table_remove_nulls(lua_State* L, int tableIdx);
}

#endif
