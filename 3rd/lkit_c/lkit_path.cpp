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

#include "lkit_path.h"
#include "libra/libra_path.h"
#include <boost/scope_exit.hpp>

void inline push_strbuf(lua_State* L, libra_strbuf* buf)
{
    lua_pushlstring(L, strbuf_cstr(buf), strbuf_length(buf));
}

static int s_path_join(lua_State* L)
{
    strbuf_init_stack(result, 64);
    BOOST_SCOPE_EXIT(result)
    {
        strbuf_finish(result);
    }
    BOOST_SCOPE_EXIT_END;

    size_t len;
    const char* path = luaL_checklstring(L, 1, &len);
    strbuf_push_lstring(result, path, len);

    int argc = lua_gettop(L);
    for (int i = 2; i <= argc; i++)
    {
        path = luaL_checklstring(L, i, &len);
        libra_path_join(result, path);
    }

    push_strbuf(L, result);
    return 1;
}

static int s_path_real(lua_State* L)
{
    strbuf_init_stack(result, 64);
    BOOST_SCOPE_EXIT(result)
    {
        strbuf_finish(result);
    };
    BOOST_SCOPE_EXIT_END;

    size_t len;
    const char* path = luaL_checklstring(L, 1, &len);

    libra_path_get_real(result, path, path + len);
    push_strbuf(L, result);
    return 1;
}

static int s_path_split(lua_State* L)
{
    strbuf_init_stack(result, 64);
    BOOST_SCOPE_EXIT(result)
    {
        strbuf_finish(result);
    };
    BOOST_SCOPE_EXIT_END;

    size_t len;
    const char* path = luaL_checklstring(L, 1, &len);
    strbuf_push_lstring(result, path, len);

    libra_path_remove_last(result);
    push_strbuf(L, result);

    libra_path_get_last(result, path, path + len);
    push_strbuf(L, result);

    return 2;
}

namespace lkit
{
    int new_path_lib(lua_State* L)
    {
        lua_createtable(L, 0, 3);

        lua_pushcfunction(L, s_path_join);
        lua_setfield(L, -2, "join");

        lua_pushcfunction(L, s_path_split);
        lua_setfield(L, -2, "split");

        lua_pushcfunction(L, s_path_real);
        lua_setfield(L, -2, "real");

        return 1;
    }
}