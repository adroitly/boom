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

#ifndef __CCEX_TILESPRITEATLAS_H__
#define __CCEX_TILESPRITEATLAS_H__

#include "cocos2d.h"

namespace ccex
{
    typedef cocos2d::Vec2 Point;
    
    class TileSpriteAtlas : public cocos2d::AtlasNode
    {
    public:
        TileSpriteAtlas();
        virtual ~TileSpriteAtlas();

        static TileSpriteAtlas* create(const char* tileFile, const char* configFile);
        bool initWithTileFile(const char* tileFile, const char* configFile);

    private:
        void updateAtlasValueAt(const Point& newPoint, const Point& oldPoint, size_t index);
        friend class TileSpriteAtlasImpl;
    };
}

#endif
