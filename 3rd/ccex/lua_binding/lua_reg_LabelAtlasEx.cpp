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
#include "ccex/LabelAtlasEx.h"
#include "cclua/cclua.hpp"

namespace ccex
{
    static int lua_createWithString(lua_State* L)
    {
        const char* text = luaL_checkstring(L, 2);

        cocos2d::Texture2D* texture;
        luaval_to_object(L, 3, "cc.Texture2D", &texture);

        int xSpace = luaL_checkint(L, 4);
        int tileWidth = luaL_checkint(L, 5);
        int tileHeight = luaL_checkint(L, 6);
        int startCharMap = luaL_checkint(L, 7);
        auto label = LabelAtlasEx::createWithString(text, texture, xSpace, tileWidth, tileHeight, startCharMap);
        object_to_luaval(L, "ccex.LabelAtlasEx", label);

        return 1;
    }

    static int lua_setString(lua_State* L)
    {
        return cclua::obj_call(L,
                               [=](LabelAtlasEx* label, const char* text)
                               {
                                   label->setString(text);
                               });
    }

    static int lua_getString(lua_State* L)
    {
        return cclua::obj_call(L,
                               [=](LabelAtlasEx* label)
                               {
                                   return label->getString();
                               });
    }

    int lua_reg_LabelAtlasEx(lua_State* L)
    {
        cclua::ToLuaCClass<ccex::LabelAtlasEx> cls(L, "LabelAtlasEx", "ccex.LabelAtlasEx", "cc.AtlasNode");

        tolua_function(L, "createWithString", lua_createWithString);
        tolua_function(L, "setString", lua_setString);
        tolua_function(L, "getString", lua_getString);

        return 1;
    }
}
