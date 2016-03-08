/*
 The MIT License (MIT)

 Copyright (c) 2015 HJC hjcapple@gmail.com

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

#ifndef __KM_RECT2_H__
#define __KM_RECT2_H__

#include "km_types.h"
#include "km_vec2.h"
#include <algorithm>

namespace km
{
    struct Rect2 final
    {
        real_t x;
        real_t y;
        real_t width;
        real_t height;

        Rect2() : x(0), y(0), width(0), height(0)
        {
        }

        Rect2(real_t x_, real_t y_, real_t w, real_t h) : x(x_), y(y_), width(w), height(h)
        {
        }

        static Rect2 makeNull()
        {
            auto val = std::numeric_limits<real_t>::infinity();
            return Rect2(val, val, 0, 0);
        }

        bool isNull() const
        {
            auto val = std::numeric_limits<real_t>::infinity();
            return x == val || y == val;
        }

        real_t getMinX() const
        {
            return x;
        }

        real_t getMinY() const
        {
            return y;
        }

        real_t getMaxX() const
        {
            return x + width;
        }

        real_t getMaxY() const
        {
            return y + height;
        }

        real_t getMidX() const
        {
            return x + width * 0.5;
        }

        real_t getMidY() const
        {
            return y + height * 0.5;
        }

        Rect2& operator*=(real_t scale)
        {
            x *= scale;
            y *= scale;
            width *= scale;
            height *= scale;
            return *this;
        }

        void inset(real_t dx, real_t dy)
        {
            x += dx;
            y += dy;
            width -= 2 * dx;
            height -= 2 * dy;
        }

        void set(real_t x, real_t y, real_t width, real_t height)
        {
            this->x = x;
            this->y = y;
            this->width = width;
            this->height = height;
        }

        bool isContainsPoint(const Vec2& pt) const;
        bool isIntersected(const Rect2& rt) const
        {
            return !isSeparated(rt);
        }

        Vec2 centerPoint() const
        {
            return Vec2(x + width * 0.5, y + height * 0.5);
        }

        void resetBounds(const Vec2& pt);
        void unionBounds(const Vec2& pt);
        void unionRect(const Rect2& rt);

        // 计算点合起来的矩形
        static Rect2 boundOfPoints(const Vec2& p0, const Vec2 p1);
        static Rect2 boundOfPoints(const Vec2& p0, const Vec2 p1, const Vec2& p2);

    private:
        bool isSeparated(const Rect2& rect) const;
    };
    
    inline bool Rect2::isContainsPoint(const Vec2& point) const
    {
        if (point.x >= getMinX() && point.x <= getMaxX() && point.y >= getMinY() && point.y <= getMaxY())
        {
            return true;
        }
        
        return false;
    }

    inline Rect2 operator*(const Rect2& rect, real_t s)
    {
        return Rect2(rect.x * s, rect.y * s, rect.width * s, rect.height * s);
    }

    inline void Rect2::resetBounds(const Vec2& pt)
    {
        x = pt.x;
        y = pt.y;
        width = height = 0;
    }

    inline void Rect2::unionBounds(const Vec2& pt)
    {
        real_t xmax = std::max(x + width, pt.x);
        real_t ymax = std::max(y + height, pt.y);

        x = std::min(pt.x, x);
        y = std::min(pt.y, y);

        width = xmax - x;
        height = ymax - y;
    }

    inline Rect2 Rect2::boundOfPoints(const Vec2& p0, const Vec2 p1)
    {
        Rect2 rt(p0.x, p0.y, 0, 0);
        rt.unionBounds(p1);
        return rt;
    }

    inline Rect2 Rect2::boundOfPoints(const Vec2& p0, const Vec2 p1, const Vec2& p2)
    {
        Rect2 rt = boundOfPoints(p0, p1);
        rt.unionBounds(p2);
        return rt;
    }
}

#endif
