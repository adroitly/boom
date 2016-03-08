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

#include "easy_lua.h"

#if LUA_VERSION_NUM == 501

#define ispseudo(i) ((i) <= LUA_REGISTRYINDEX)

//int lua_absindex(lua_State* L, int idx)
//{
//    if (idx > 0 || ispseudo(idx))
//    {
//        return idx;
//    }
//    return lua_gettop(L) + idx + 1;
//}

static const char* luaL_tolstring(lua_State* L, int idx, size_t* len)
{
    if (!luaL_callmeta(L, idx, "__tostring"))
    { /* no metafield? */
        switch (lua_type(L, idx))
        {
            case LUA_TNUMBER:
            case LUA_TSTRING:
                lua_pushvalue(L, idx);
                break;
            case LUA_TBOOLEAN:
                lua_pushstring(L, (lua_toboolean(L, idx) ? "true" : "false"));
                break;
            case LUA_TNIL:
                lua_pushliteral(L, "nil");
                break;
            default:
                lua_pushfstring(L, "%s: %p", luaL_typename(L, idx), lua_topointer(L, idx));
                break;
        }
    }
    return lua_tolstring(L, -1, len);
}

#endif

namespace easy_lua
{
    static void getfield_ex_impl(lua_State* L, int idx, const char* begin, const char* end)
    {
        if (begin >= end)
        {
            lua_pushnil(L);
            return;
        }

        lua_pushvalue(L, idx);
        for (;;)
        {
            auto ptr = std::find(begin, end, '.');
            lua_pushlstring(L, begin, ptr - begin);
            lua_gettable(L, -2);

            if (ptr == end)
            {
                break;
            }

            if (!lua_istable(L, -1))
            {
                lua_pop(L, 1);
                lua_pushnil(L);
                break;
            }

            lua_replace(L, -2);
            begin = ptr + 1;
        }
        lua_replace(L, -2);
    }

    void getfield_ex(lua_State* L, int idx, const char* k)
    {
        getfield_ex_impl(L, idx, k, k + strlen(k));
    }

    void getfield_ex(lua_State* L, int idx, const std::string& k)
    {
        const char* cstr = k.c_str();
        getfield_ex_impl(L, idx, cstr, cstr + k.size());
    }

#if LUA_VERSION_NUM == 501
    void push_globals(lua_State* L)
    {
        lua_pushvalue(L, LUA_GLOBALSINDEX);
    }
#else
    void push_globals(lua_State* L)
    {
        lua_rawgeti(L, LUA_REGISTRYINDEX, LUA_RIDX_GLOBALS);
    }
#endif

    static void fprintStack(lua_State* L, FILE* file)
    {
        int n = lua_gettop(L);
        if (n == 0)
        {
            fprintf(file, "stack is empty.\n");
            return;
        }

        fprintf(file, "stack size: %ld\n", (long)n);
        fprintf(file, "----\n");

        for (int i = n; i >= 1; i--)
        {
            fprintf(file, "[%d,%d,%s]: ", i - n - 1, i, luaL_typename(L, i));
            fprintf(file, "%s\n", luaL_tolstring(L, i, nullptr));
            lua_pop(L, 1);
        }
        fprintf(file, "----\n");
    }

    void print_stack(lua_State* L)
    {
        fprintStack(L, stdout);
    }

    static int traceback(lua_State* L)
    {
        const char* msg = lua_tostring(L, 1);
        if (msg)
        {
            luaL_traceback(L, L, msg, 1);
        }
        else if (!lua_isnoneornil(L, 1))
        {                                           /* is there an error object? */
            if (!luaL_callmeta(L, 1, "__tostring")) /* try its 'tostring' metamethod */
            {
                lua_pushliteral(L, "(no error message)");
            }
        }
        return 1;
    }

    bool safe_call(lua_State* L, int narg, int nres)
    {
        int status;
        int base = lua_gettop(L) - narg;           /* function index */
        lua_pushcfunction(L, easy_lua::traceback); /* push traceback function */
        lua_insert(L, base);                       /* put it under chunk and args */
        status = lua_pcall(L, narg, nres, base);
        lua_remove(L, base); /* remove traceback function */
        return status == 0;
    }

    int table_maxn(lua_State* L, int idx)
    {
        int maxn = 0;
        table_walk(L,
                   idx,
                   [&](int keyIdx, int)
                   {
                       if (lua_type(L, keyIdx) == LUA_TNUMBER)
                       {
                           int num = lua_tonumber(L, keyIdx);
                           maxn = std::max(maxn, num);
                       }
                   });
        return maxn;
    }

    /*
    void table_remove_nulls(lua_State* L, int idx)
    {
        idx = lua_absindex(L, idx);
        int len = table_maxn(L, idx);

        int k = 1;
        for (int i = 1; i <= len; i++)
        {
            lua_rawgeti(L, idx, i);
            if (!lua_isnil(L, -1))
            {
                if (i != k)
                {
                    lua_pushvalue(L, -1);
                    lua_rawseti(L, idx, k);
                }
                k++;
            }
            lua_pop(L, 1);
        }

        for (int i = k; i <= len; i++)
        {
            lua_pushnil(L);
            lua_rawseti(L, idx, i);
        }
    }
     */
}