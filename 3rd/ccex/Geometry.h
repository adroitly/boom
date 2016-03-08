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

#ifndef __CCEX_GEOMETRYUTILS_H__
#define __CCEX_GEOMETRYUTILS_H__

#include "cocos2d.h"
#include <cmath>

namespace ccex
{
    cocos2d::Rect rect_inset(const cocos2d::Rect& rt, float dx, float dy);

    cocos2d::Vec2 rect_getMiddle(const cocos2d::Rect& rect);
    void rect_setMiddle(cocos2d::Rect* rect, const cocos2d::Vec2& middle);

    inline cocos2d::Vec2 size_getMiddle(const cocos2d::Size& size)
    {
        return cocos2d::Point(size.width * 0.5, size.height * 0.5);
    }

    inline cocos2d::Vec2 point_offset(const cocos2d::Vec2& pt, float xOffset, float yOffset)
    {
        return cocos2d::Point(pt.x + xOffset, pt.y + yOffset);
    }

    inline cocos2d::Vec2 point_move(const cocos2d::Vec2& pt, float length, float angle)
    {
        return point_offset(pt, length * std::cos(angle), length * std::sin(angle));
    }

    cocos2d::Vec2 rect_adjustPointInside(const cocos2d::Vec2& rect, const cocos2d::Point& pt);
}

#endif
