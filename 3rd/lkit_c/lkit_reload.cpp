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

#include "lkit_reload.h"
#include <assert.h>

namespace lkit
{
    static int s_table_copy(lua_State* L, int idx)
    {
        assert(idx > 0);

        lua_newtable(L);
        int newIdx = lua_gettop(L);

        lua_pushvalue(L, idx);
        lua_pushnil(L);

        while (lua_next(L, -2))
        {
            lua_pushvalue(L, -2);
            lua_insert(L, -2);
            lua_rawset(L, newIdx);
        }
        lua_pop(L, 1);

        return 1;
    }

    int save_package(lua_State* L)
    {
        lua_getglobal(L, "package");
        lua_getfield(L, -1, "loaded");

        s_table_copy(L, lua_gettop(L));
        lua_insert(L, 1);

        lua_pop(L, 2);
        return 1;
    }

    static bool s_valueIsNull(lua_State* L, int idx, int key)
    {
        lua_pushvalue(L, key);
        lua_rawget(L, idx);
        bool result = lua_isnil(L, -1);
        lua_pop(L, 1);
        return result;
    }

    int reload_package(lua_State* L)
    {
        if (!lua_istable(L, 1))
        {
            return 0;
        }

        int saveLoadedIdx = 1;
        lua_getglobal(L, "package");
        lua_getfield(L, -1, "loaded");
        int loadedIdx = lua_gettop(L);

        s_table_copy(L, loadedIdx);
        lua_pushnil(L);
        while (lua_next(L, -2))
        {
            if (s_valueIsNull(L, saveLoadedIdx, -2))
            {
                lua_pushvalue(L, -2);
                lua_pushnil(L);
                lua_rawset(L, loadedIdx);
            }
            lua_pop(L, 1);
        }
        lua_pop(L, 4);
        return 0;
    }
}
