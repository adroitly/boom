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

#include "lua_reg_ccex.h"
#include "LuaBasicConversions.h"
#include "libra/libra_fsys.h"
#include "cclua/cclua.hpp"
#include <boost/scope_exit.hpp>

#if CC_TARGET_PLATFORM == CC_PLATFORM_ANDROID

#include "unzip.h"
#include "jni/Java_org_cocos2dx_lib_Cocos2dxHelper.h"
std::vector<std::string> package_subItemNames(const std::string& basePath)
{
    std::vector<std::string> names;
    unzFile pFile = nullptr;
    std::string floder = basePath;
    // floder必须以/结尾
    if (floder.back() != '/')
    {
        floder.push_back('/');
    }

    do
    {
        std::string resourcePath = getApkPath();
        CCLOG("resourcePath = %s", resourcePath.c_str());
        pFile = cocos2d::unzOpen(resourcePath.c_str());
        CC_BREAK_IF(!pFile);
        CC_BREAK_IF(floder.empty());
        CC_BREAK_IF(!pFile);
        CCLOG("floder = %s", floder.c_str());
        int nRet = cocos2d::unzLocateFile(pFile, floder.c_str(), 0);
        CCLOG("nRet = %d", nRet);
        CC_BREAK_IF(UNZ_OK != nRet);
        while (cocos2d::unzGoToNextFile(pFile) == UNZ_OK)
        {
            char szFilePathA[260];
            cocos2d::unz_file_info FileInfo;
            nRet = unzGetCurrentFileInfo(pFile, &FileInfo, szFilePathA, sizeof(szFilePathA), NULL, 0, NULL, 0);
            CC_BREAK_IF(UNZ_OK != nRet);
            std::string path(szFilePathA);  //最后一个为/为目录过滤掉，且开头必须以文件开头
            if (path[path.size() - 1] != '/' && path.find_first_of(floder) == 0)
            {
                names.insert(names.begin(), std::string(szFilePathA));
            }
        }

    } while (0);

    if (pFile)
    {
        cocos2d::unzClose(pFile);
    }

    return std::move(names);
}

static int s_path_subItemNames(lua_State* L)
{
    const char* path = luaL_checkstring(L, 1);
    std::string basePath = cocos2d::FileUtils::getInstance()->fullPathForFilename(path);
    std::vector<std::string> names = package_subItemNames(basePath);
    ccvector_std_string_to_luaval(L, names);
    return 1;
}

#else

static bool walk_fun(const char* refPath, const char* name, fsys_file_type filetype, void* ctx)
{
    auto names = (std::vector<std::string>*)ctx;
    names->push_back(name);
    return false;
}

static int s_path_subItemNames(lua_State* L)
{
    const char* path = luaL_checkstring(L, 1);
    std::string basePath = cocos2d::FileUtils::getInstance()->fullPathForFilename(path);
    std::vector<std::string> names;
    fsys_dir_walk(basePath.c_str(), walk_fun, &names);
    ccvector_std_string_to_luaval(L, names);
    return 1;
}

#endif

namespace ccex
{
    static cocos2d::Node* node_hitTest(cocos2d::Node* node, const cocos2d::Vec2& pt)
    {
        for (auto child : node->getChildren())
        {
            auto tranform = child->getParentToNodeAffineTransform();
            auto tmpPt = cocos2d::PointApplyAffineTransform(pt, tranform);
            auto result = node_hitTest(child, tmpPt);
            if (result)
            {
                return result;
            }
        }

        if (!node->isVisible())
        {
            return nullptr;
        }

        cocos2d::Rect rt;
        rt.size = node->getContentSize();

        if (rt.containsPoint(pt))
        {
            return node;
        }
        return nullptr;
    }

    static int lua_node_hitTest(lua_State* L)
    {
        auto node = (cocos2d::Node*)tolua_tousertype(L, 1, 0);
        cocos2d::Vec2 pt;
        luaval_to_vec2(L, 2, &pt);
        if (node == nullptr)
        {
            lua_pushnil(L);
            return 1;
        }
        auto ret = node_hitTest(node, pt);
        object_to_luaval<cocos2d::Node>(L, "cc.Node", (cocos2d::Node*)ret);
        return 1;
    }

    static void onTouchEvent(cocos2d::Layer* layer, cocos2d::Touch* touch, cocos2d::EventTouch* event)
    {
        if (event == nullptr)
        {
            return;
        }

        switch (event->getEventCode())
        {
            case EventTouch::EventCode::BEGAN:
                layer->onTouchBegan(touch, event);
                break;

            case EventTouch::EventCode::MOVED:
                layer->onTouchMoved(touch, event);
                break;

            case EventTouch::EventCode::ENDED:
                layer->onTouchEnded(touch, event);
                break;

            case EventTouch::EventCode::CANCELLED:
                layer->onTouchCancelled(touch, event);
                break;

            default:
                CCASSERT(false, "The eventcode is invalid.");
                break;
        }
    }
    
    static int s_loadData(lua_State* L)
    {
        const char* path = luaL_checkstring(L, 1);
        auto data = cocos2d::FileUtils::getInstance()->getDataFromFile(path);
//        if (data.isNull())
//        {
//            std::string str = path;
//            str += " file not find";
//            luaL_error(L, str.c_str());
//        }
        lua_pushlstring(L, (char*)data.getBytes(), data.getSize());
        return 1;
    }

    static int s_onTouchEvent(lua_State* L)
    {
        return cclua::obj_call(L,
                               [=](cocos2d::Layer* layer, cclua::Index touchIdx, cclua::Index eventIdx)
                               {
                                   cocos2d::Touch* touch;
                                   cocos2d::EventTouch* event;

                                   luaval_to_object(L, touchIdx.val, "cc.Touch", &touch);
                                   luaval_to_object(L, eventIdx.val, "cc.EventTouch", &event);

                                   onTouchEvent(layer, touch, event);
                               });
    }

    int lua_reg_RefCache(lua_State* L);
    int lua_reg_RefSet(lua_State* L);
    int lua_reg_LabelAtlasEx(lua_State* L);

    int lua_reg_ccex(lua_State* L)
    {
        tolua_open(L);
        tolua_module(L, "ccex", 0);
        tolua_beginmodule(L, "ccex");
        BOOST_SCOPE_EXIT(L)
        {
            tolua_endmodule(L);
        }
        BOOST_SCOPE_EXIT_END;

        tolua_function(L, "hitTest", lua_node_hitTest);
        tolua_function(L, "subItemNames", s_path_subItemNames);
        tolua_function(L, "onTouchEvent", s_onTouchEvent);
        tolua_function(L, "loadData", s_loadData);

        lua_reg_RefCache(L);
        lua_reg_RefSet(L);
        lua_reg_LabelAtlasEx(L);

        return 1;
    }
}
