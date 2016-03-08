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

#include "lkit_openlibs.h"
#include "lkit_reload.h"
#include "lkit_fsys.h"
#include "lkit_path.h"
#include <assert.h>

namespace lkit
{
    int newlibs(lua_State* L)
    {
        lua_createtable(L, 0, 4);

        lua_pushcfunction(L, save_package);
        lua_setfield(L, -2, "save_package");

        lua_pushcfunction(L, reload_package);
        lua_setfield(L, -2, "reload_package");

        new_fsys_lib(L);
        lua_setfield(L, -2, "fsys");
        
        new_path_lib(L);
        lua_setfield(L, -2, "path");

        return 1;
    }

    void openlibs(lua_State* L)
    {
        newlibs(L);
        lua_setglobal(L, "lkit");
    }
}