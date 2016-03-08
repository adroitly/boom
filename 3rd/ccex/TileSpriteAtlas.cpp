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

#include "TileSpriteAtlas.h"
extern "C" {
#include "lua.h"
#include "lualib.h"
#include "lauxlib.h"
}
using namespace cocos2d;

#undef CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
#define CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL 1

namespace ccex
{
    typedef cocos2d::Size Size;

    struct ReadContent
    {
        ReadContent()
        {
            atlas = nullptr;
            tileFile = nullptr;
            result = true;
            total_items = 0;
            current_item_index = 0;
        }
        TileSpriteAtlas* atlas;
        const char* tileFile;
        Size size;
        Size tile_size;
        size_t total_items;
        size_t current_item_index;
        bool result;
    };

    struct TileSpriteAtlasImpl
    {
        static bool initWithTileFile(const ReadContent& content);
        static void updateAtlasValueAt(const ReadContent& content, const Point& newPoint, const Point& oldPoint);
    };

    static void s_getList(lua_State* L, int tableIdx, float* values, size_t size)
    {
        for (size_t i = 0; i < size; i++)
        {
            lua_rawgeti(L, tableIdx, (int)i + 1);
            values[i] = lua_tonumber(L, -1);
            lua_pop(L, 1);
        }
    }

    static int lib_info(lua_State* L)
    {
        ReadContent* content = (ReadContent*)lua_touserdata(L, lua_upvalueindex(1));
        assert(lua_istable(L, 1));

        lua_getfield(L, 1, "size");
        s_getList(L, -1, &content->size.width, 2);

        lua_getfield(L, 1, "tile_size");
        s_getList(L, -1, &content->tile_size.width, 2);

        lua_getfield(L, 1, "total_items");
        content->total_items = lua_tonumber(L, -1);

        content->result = TileSpriteAtlasImpl::initWithTileFile(*content);

        return 0;
    }

    static int lib_item(lua_State* L)
    {
        ReadContent* content = (ReadContent*)lua_touserdata(L, lua_upvalueindex(1));
        if (!content->result)
        {
            return 0;
        }

        Point pts[2];
        s_getList(L, 1, &pts[0].x, 4);

        pts[1].y = content->size.height - (pts[1].y + content->tile_size.height);
        TileSpriteAtlasImpl::updateAtlasValueAt(*content, pts[0], pts[1]);
        content->current_item_index++;
        return 0;
    }

#if COCOS2D_VERSION >= 0x00030000
    static void lib_dofile(lua_State* L, const char* filePath)
    {
        auto fileData = cocos2d::FileUtils::getInstance()->getDataFromFile(filePath);
        luaL_loadbuffer(L, (char*)fileData.getBytes(), fileData.getSize(), "");
        lua_call(L, 0, 0);
    }
#else
    static void lib_dofile(lua_State* L, const char* filePath)
    {
        unsigned long dataSize;
        auto fileUtils = cocos2d::CCFileUtils::sharedFileUtils();
        char* fileData = (char*)fileUtils->getFileData(filePath, "r", &dataSize);
        luaL_loadbuffer(L, fileData, dataSize, "");
        lua_call(L, 0, 0);
        delete[] fileData;
    }
#endif

    TileSpriteAtlas::TileSpriteAtlas()
    {
    }

    TileSpriteAtlas::~TileSpriteAtlas()
    {
    }

    TileSpriteAtlas* TileSpriteAtlas::create(const char* tileFile, const char* configFile)
    {
        TileSpriteAtlas* pRet = new TileSpriteAtlas();
        if (pRet->initWithTileFile(tileFile, configFile))
        {
            pRet->autorelease();
            return pRet;
        }
        CC_SAFE_DELETE(pRet);
        return NULL;
    }

    bool TileSpriteAtlas::initWithTileFile(const char* tileFile, const char* configFile)
    {
        lua_State* L = luaL_newstate();

        ReadContent content;
        content.atlas = this;
        content.tileFile = tileFile;

        lua_pushlightuserdata(L, &content);
        lua_pushcclosure(L, lib_info, 1);
        lua_setglobal(L, "info");

        lua_pushlightuserdata(L, &content);
        lua_pushcclosure(L, lib_item, 1);
        lua_setglobal(L, "item");

        lib_dofile(L, configFile);

        lua_close(L);

        setContentSize(content.size);

        return content.result;
    }

    void TileSpriteAtlas::updateAtlasValueAt(const Point& newPoint, const Point& oldPoint, size_t index)
    {
#if COCOS2D_VERSION >= 0x00030000
        V3F_C4B_T2F_Quad quad;
        auto pTextureAtlas = _textureAtlas;
        auto itemWidth = _itemWidth;
        auto itemHeight = _itemHeight;
        typedef cocos2d::Color4B Color4B;
#else
        ccV3F_C4B_T2F_Quad quad;
        auto pTextureAtlas = m_pTextureAtlas;
        auto itemWidth = m_uItemWidth;
        auto itemHeight = m_uItemHeight;
        typedef cocos2d::ccColor4B Color4B;
#endif

        float textureWide = (float)(pTextureAtlas->getTexture()->getPixelsWide());
        float textureHigh = (float)(pTextureAtlas->getTexture()->getPixelsHigh());

        float itemWidthInPixels = itemWidth * CC_CONTENT_SCALE_FACTOR();
        float itemHeightInPixels = itemHeight * CC_CONTENT_SCALE_FACTOR();

#if CC_FIX_ARTIFACTS_BY_STRECHING_TEXEL
        float left = (2 * newPoint.x + 1) / (2 * textureWide);
        float right = left + (itemWidthInPixels * 2 - 2) / (2 * textureWide);
        float top = (2 * newPoint.y + 1) / (2 * textureHigh);
        float bottom = top + (itemHeightInPixels * 2 - 2) / (2 * textureHigh);
#else
        float left = (newPoint.x) / textureWide;
        float right = left + itemWidthInPixels / textureWide;
        float top = (newPoint.y) / textureHigh;
        float bottom = top + itemHeightInPixels / textureHigh;
#endif

        quad.tl.texCoords.u = left;
        quad.tl.texCoords.v = top;
        quad.tr.texCoords.u = right;
        quad.tr.texCoords.v = top;
        quad.bl.texCoords.u = left;
        quad.bl.texCoords.v = bottom;
        quad.br.texCoords.u = right;
        quad.br.texCoords.v = bottom;

        quad.bl.vertices.x = (float)oldPoint.x;
        quad.bl.vertices.y = (float)oldPoint.y;
        quad.bl.vertices.z = 0.0f;
        quad.br.vertices.x = (float)(oldPoint.x + itemWidth);
        quad.br.vertices.y = (float)(oldPoint.y);
        quad.br.vertices.z = 0.0f;
        quad.tl.vertices.x = (float)(oldPoint.x);
        quad.tl.vertices.y = (float)(oldPoint.y + itemHeight);
        quad.tl.vertices.z = 0.0f;
        quad.tr.vertices.x = (float)(oldPoint.x + itemWidth);
        quad.tr.vertices.y = (float)(oldPoint.y + itemHeight);
        quad.tr.vertices.z = 0.0f;

        Color4B color = { _displayedColor.r, _displayedColor.g, _displayedColor.b, _displayedOpacity };
        quad.tr.colors = color;
        quad.tl.colors = color;
        quad.br.colors = color;
        quad.bl.colors = color;

        pTextureAtlas->updateQuad(&quad, index);
    }

    bool TileSpriteAtlasImpl::initWithTileFile(const ReadContent& content)
    {
        return content.atlas->AtlasNode::initWithTileFile(content.tileFile,
                                                            content.tile_size.width,
                                                            content.tile_size.height,
                                                            (int)content.total_items);
    }

    void TileSpriteAtlasImpl::updateAtlasValueAt(const ReadContent& content,
                                                 const Point& newPoint,
                                                 const Point& oldPoint)
    {
        content.atlas->updateAtlasValueAt(newPoint, oldPoint, content.current_item_index);
    }
}
