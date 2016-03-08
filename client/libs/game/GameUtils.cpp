//
//  GameUtils.cpp
//  WeAreHeros
//
//  Created by HJC on 14/12/29.
//
//

#include "GameUtils.h"
#include "CCLuaEngine.h"
#include "FlaSDK.h"
#include "ccex/RefCache.h"
#include "libra/libra_fsys.h"
#include "clover/Data.h"
#include "libra/libra_fsys.h"
#include "libra/libra_path.h"
#include "rc4/rc4.h"


using namespace cocos2d;
namespace GameUtils
{
    static std::string s_packagePath;
    static std::string s_resourcePath;

    void removeAllUnusedResources()
    {
        cocos2d::SpriteFrameCache::getInstance()->removeUnusedSpriteFrames();
        cocos2d::Director::getInstance()->purgeCachedData();
        FlaSDK::purgeCachedData();
        ccex::RefCache::getInstance()->removeAll();
    }

    std::string getResourcePath()
    {
        if (s_resourcePath.empty())
        {
            auto directory = cocos2d::FileUtils::getInstance()->getWritablePath();
            s_resourcePath = libra::path_join(directory, "Resources");
            fsys_let_dir_exists(s_resourcePath.c_str());
        }
        return s_resourcePath;
    }
    
    void removeDirContent(const std::string& path)
    {
        fsys_rmdir_contents(path.c_str());
    }

    void setPackagePath(const std::string& path)
    {
        s_packagePath = path;
    }

    std::string getPackagePath()
    {
        return s_packagePath;
    }

    static std::vector<char> decryptData(const std::vector<char>& inputBuf)
    {
        std::vector<char> result;

        rc4::Sbox sbox;
        init(&sbox, "luanqibazaoshenmegui");
        crypt(&sbox, inputBuf, &result);

        return std::move(result);
    }

    void saveDecryptString(const std::string& content, const std::string& filePath)
    {
        std::vector<char> data;
        data.resize(content.size());
        data.assign(content.begin(), content.end());
        data = decryptData(data);

        FILE* file = fopen(filePath.c_str(), "wb");
        if (file != nullptr)
        {
            for (auto ch : data)
            {
                fputc(ch, file);
            }
        }
        fclose(file);
    }

    std::string readDecryptFile(const std::string& filePath)
    {
        using namespace std;
        auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
        vector<char> data = vector<char>(fileData.getBytes(), fileData.getBytes() + fileData.getSize());
        data = decryptData(data);
        return string(data.begin(), data.end());
    }
    
    void callLuaFunction(const std::string& funName)
    {
        lua_State* L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
        lua_getglobal(L, funName.c_str());
        if (LUA_TFUNCTION == lua_type(L, -1))
        {
            lua_pcall(L, 0, 0, 0);
        }
        else
        {
            CCLog("Lua未注册全局函数%s", funName.c_str());
        }
    }
    
    void callLuaFunction(const std::string& funName, const char* value)
    {
        lua_State* L = LuaEngine::getInstance()->getLuaStack()->getLuaState();
        lua_getglobal(L, funName.c_str());
        if (LUA_TFUNCTION == lua_type(L, -1))
        {
            lua_pushstring(L, value);
            lua_pcall(L, 1, 0, 0);
        }
        else
        {
            CCLog("Lua未注册全局函数%s", funName.c_str());
        }
    }
}