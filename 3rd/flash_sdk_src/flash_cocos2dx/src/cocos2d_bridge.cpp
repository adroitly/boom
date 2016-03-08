//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "../FlaConfig.h"
#include "clover/ScopeGuard.h"
#include "../FlaResourceCache.h"
#include "fla_Settings.h"
using namespace cocos2d;

namespace cocos2d_bridge
{
    static fla::TextureFrame* createTextureFrame(uint64_t textureId,
                                                 const Rect& frame,
                                                 bool rotated,
                                                 const Point& offset,
                                                 const Size& sourceSize)
    {
        auto rectInPixels = frame;
        auto rect = fla::pixels_to_points(rectInPixels);
        return fla::TextureFrame::create(textureId, rect, rectInPixels, rotated);
    }
}

// cocos2dx 内部没有容错，所以将装载过程再编写一下
#if COCOS2D_VERSION >= 0x00030000
namespace cocos2d_bridge
{
    bool loadFramesWithPlistFile(const std::string& plistPath, uint64_t textureId)
    {
        std::string fullPath = FileUtils::getInstance()->fullPathForFilename(plistPath);
        ValueMap dictionary = FileUtils::getInstance()->getValueMapFromFile(fullPath);
        if (dictionary.empty())
        {
            return false;
        }
        
        auto& framesValue = dictionary["frames"];
        auto& metadataValue = dictionary["metadata"];
        
        if (framesValue.isNull() || metadataValue.isNull())
        {
            return false;
        }
        
        ValueMap& framesDict = framesValue.asValueMap();
        int format = 0;
        
        // get the format
        if (dictionary.find("metadata") != dictionary.end())
        {
            ValueMap& metadataDict = metadataValue.asValueMap();
            format = metadataDict["format"].asInt();
        }
        
        if (format != 1 && format != 2)
        {
            return false;
        }
        
        for (auto iter = framesDict.begin(); iter != framesDict.end(); ++iter)
        {
            ValueMap& frameDict = iter->second.asValueMap();
            std::string spriteFrameName = iter->first;
            
            Rect frame = RectFromString(frameDict["frame"].asString());
            bool rotated = false;
            
            // rotation
            if (format == 2)
            {
                rotated = frameDict["rotated"].asBool();
            }
            
            Vec2 offset = PointFromString(frameDict["offset"].asString());
            Size sourceSize = SizeFromString(frameDict["sourceSize"].asString());
            
            // create frame
            auto spriteFrame = createTextureFrame(textureId, frame, rotated, offset, sourceSize);
            FlaResourceCache::getInstance().setTextureFrame(spriteFrame, spriteFrameName);
        }
        return true;
    }
}

#else

namespace cocos2d_bridge
{
    bool loadFramesWithPlistFile(const std::string& plistPath, uint64_t textureId)
    {
        std::string fullPath = CCFileUtils::sharedFileUtils()->fullPathForFilename(plistPath.c_str());
        CCDictionary* dictionary = CCDictionary::createWithContentsOfFileThreadSafe(fullPath.c_str());
        if (dictionary == NULL)
        {
            return false;
        }
        
        CLOVER_SCOPE_EXIT
        {
            dictionary->release();
        };
        
        CCDictionary* metadataDict = (CCDictionary*)dictionary->objectForKey("metadata");
        CCDictionary* framesDict = (CCDictionary*)dictionary->objectForKey("frames");
        if (metadataDict == NULL || framesDict == NULL)
        {
            return false;
        }
        
        int format = metadataDict->valueForKey("format")->intValue();
        if (format != 1 && format != 2)
        {
            return false;
        }
        
        CCDictElement* pElement = NULL;
        CCDICT_FOREACH(framesDict, pElement)
        {
            CCDictionary* frameDict = (CCDictionary*)pElement->getObject();
            std::string spriteFrameName = pElement->getStrKey();
            CCRect frame = CCRectFromString(frameDict->valueForKey("frame")->getCString());
            bool rotated = false;
            
            // rotation
            if (format == 2)
            {
                rotated = frameDict->valueForKey("rotated")->boolValue();
            }
            
            CCPoint offset = CCPointFromString(frameDict->valueForKey("offset")->getCString());
            CCSize sourceSize = CCSizeFromString(frameDict->valueForKey("sourceSize")->getCString());
            
            // create frame
            auto spriteFrame = createTextureFrame(textureId, frame, rotated, offset, sourceSize);
            FlaResourceCache::getInstance().setTextureFrame(spriteFrame, spriteFrameName);
        }
        return true;
    }
}
#endif

extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}

namespace cocos2d_bridge
{
    static void lua_to_pair(lua_State* L, int idx, float* v0, float* v1)
    {
        if (lua_istable(L, idx))
        {
            lua_rawgeti(L, idx, 1);
            *v0 = lua_tonumber(L, -1);
            lua_pop(L, 1);
            
            lua_rawgeti(L, idx, 2);
            *v1 = lua_tonumber(L, -1);
            lua_pop(L, 1);
        }
    }
    
    static Point lua_to_point(lua_State* L, int idx)
    {
        Point pt;
        lua_to_pair(L, idx, &pt.x, &pt.y);
        return pt;
    }
    
    static std::string lua_to_string(lua_State* L, int idx)
    {
        size_t len;
        auto str = lua_tolstring(L, idx, &len);
        return std::string(str, str + len);
    }
    
    static Size lua_to_size(lua_State* L, int idx)
    {
        Size size;
        lua_to_pair(L, idx, &size.width, &size.height);
        return size;
    }
    
    static Rect lua_to_rect(lua_State* L, int idx)
    {
        Rect rt;
        if (lua_istable(L, idx))
        {
            lua_rawgeti(L, idx, 1);
            rt.origin.x = lua_tonumber(L, -1);
            lua_pop(L, 1);
            
            lua_rawgeti(L, idx, 2);
            rt.origin.y = lua_tonumber(L, -1);
            lua_pop(L, 1);
            
            lua_rawgeti(L, idx, 3);
            rt.size.width = lua_tonumber(L, -1);
            lua_pop(L, 1);
            
            lua_rawgeti(L, idx, 4);
            rt.size.height = lua_tonumber(L, -1);
            lua_pop(L, 1);
        }
        return rt;
    }
    
    static int lua_frame(lua_State* L)
    {
        uint64_t* textureId = (uint64_t*)lua_touserdata(L, lua_upvalueindex(1));
        if (lua_istable(L, 1))
        {
            lua_getfield(L, 1, "frame");
            auto frame = lua_to_rect(L, -1);
            lua_pop(L, 1);
            
            lua_getfield(L, 1, "sourceSize");
            auto sourceSize = lua_to_size(L, -1);
            lua_pop(L, 1);
            
            lua_getfield(L, 1, "offset");
            auto offset = lua_to_point(L, -1);
            lua_pop(L, 1);
            
            lua_getfield(L, 1, "rotated");
            auto rotated = lua_toboolean(L, -1);
            lua_pop(L, 1);
            
            auto spriteFrame = createTextureFrame(*textureId, frame, rotated, offset, sourceSize);
            lua_getfield(L, 1, "key");
            FlaResourceCache::getInstance().setTextureFrame(spriteFrame, lua_to_string(L, -1));
            lua_pop(L, 1);
        }
        return 1;
    }
    
    static int lua_metadata(lua_State* L)
    {
        return 1;
    }
    
    static int traceback(lua_State* L)
    {
        return 1;
    }
    
    static bool lua_safe_call(lua_State* L, int narg, int nres)
    {
        int status;
        int base = lua_gettop(L) - narg; /* function index */
        lua_pushcfunction(L, traceback); /* push traceback function */
        lua_insert(L, base);             /* put it under chunk and args */
        status = lua_pcall(L, narg, nres, base);
        lua_remove(L, base); /* remove traceback function */
        return status == 0;
    }
    
    bool loadFramesWithLuaFile(const std::string& path, uint64_t textureId)
    {
        lua_State* L = luaL_newstate();
        CLOVER_SCOPE_EXIT
        {
            lua_close(L);
        };
        
        lua_pushlightuserdata(L, &textureId);
        lua_pushcclosure(L, lua_frame, 1);
        lua_setglobal(L, "frame");
        
        lua_pushlightuserdata(L, &textureId);
        lua_pushcclosure(L, lua_metadata, 1);
        lua_setglobal(L, "metadata");
        
        if (luaL_loadfile(L, path.c_str()) == 0)
        {
            if (lua_safe_call(L, 0, 0))
            {
                return true;
            }
        }
        return false;
    }
}
