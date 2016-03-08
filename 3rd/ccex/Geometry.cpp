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

#include "Geometry.h"

namespace ccex
{
    static float letBetween(float value, float minV, float maxV)
    {
        if (minV > maxV)
        {
            std::swap(minV, maxV);
        }
        value = std::max(value, minV);
        value = std::min(value, maxV);
        return value;
    }

    cocos2d::Vec2 rect_adjustPointInside(const cocos2d::Rect& rect, const cocos2d::Vec2& pt)
    {
        cocos2d::Point result;
        result.x = letBetween(pt.x, rect.getMinX(), rect.getMaxX());
        result.y = letBetween(pt.y, rect.getMinY(), rect.getMaxY());
        return result;
    }

    cocos2d::Rect rect_inset(const cocos2d::Rect& rt, float dx, float dy)
    {
        cocos2d::Rect result = rt;
        result.origin.x += dx;
        result.origin.y += dy;
        result.size.width -= 2 * dx;
        result.size.height -= 2 * dy;
        return rt;
    }
    
    cocos2d::Point rect_getMiddle(const cocos2d::Rect& rect)
    {
        return cocos2d::Point(rect.getMidX(), rect.getMidY());
    }
    
    void rect_setMiddle(cocos2d::Rect* rect, const cocos2d::Vec2& middle)
    {
        rect->origin.x = middle.x - rect->size.width * 0.5;
        rect->origin.y = middle.y - rect->size.height * 0.5;
    }
}