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

#ifndef __KM_VEC2_H__
#define __KM_VEC2_H__

#include "km_types.h"
#include <limits>
#include <algorithm>

namespace km
{
    struct Vec2 final
    {
        real_t x;
        real_t y;

        Vec2() : x(0), y(0)
        {
        }

        Vec2(real_t x_, real_t y_) : x(x_), y(y_)
        {
        }

        static Vec2 makeZero()
        {
            return Vec2(0, 0);
        }

        static Vec2 makeNull()
        {
            auto val = std::numeric_limits<real_t>::infinity();
            return Vec2(val, val);
        }

        bool isNull() const
        {
            auto val = std::numeric_limits<real_t>::infinity();
            return x == val || y == val;
        }

        static Vec2 makeMax()
        {
            auto val = std::numeric_limits<real_t>::max();
            return Vec2(val, val);
        }

        static Vec2 makeMin()
        {
            auto val = std::numeric_limits<real_t>::min();
            return Vec2(val, val);
        }

        static void unionVec(Vec2& minPt, Vec2& maxPt, const Vec2& pt)
        {
            minPt.x = std::min(pt.x, minPt.x);
            minPt.y = std::min(pt.y, minPt.y);
            maxPt.x = std::max(pt.x, maxPt.x);
            maxPt.y = std::max(pt.y, maxPt.y);
        }

        void set(real_t x_, real_t y_)
        {
            x = x_;
            y = y_;
        }

        Vec2& operator*=(real_t s)
        {
            x *= s;
            y *= s;
            return *this;
        }

        Vec2& operator+=(const Vec2& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        Vec2& operator-=(const Vec2& rhs)
        {
            x += rhs.x;
            y += rhs.y;
            return *this;
        }

        bool equals(const Vec2& rhs, real_t epsilon) const
        {
            return std::fabs(x - rhs.x) <= epsilon && std::fabs(y - rhs.y) <= epsilon;
        }

        real_t dotMult(const Vec2& rhs) const
        {
            return x * rhs.x + y * rhs.y;
        }

        real_t crossMult(const Vec2& rhs) const
        {
            return x * rhs.y - y * rhs.x;
        }

        real_t length() const
        {
            return std::sqrt(x * x + y * y);
        }

        real_t lengthSQ() const
        {
            return x * x + y * y;
        }

        Vec2 normalize() const;
    };

    inline Vec2 lerp(const Vec2& lhs, const Vec2& rhs, real_t ratio)
    {
        auto x = s_lerp(lhs.x, rhs.x, ratio);
        auto y = s_lerp(lhs.y, rhs.y, ratio);
        return Vec2(x, y);
    }

    inline Vec2 Vec2::normalize() const
    {
        real_t l = 1.0 / length();
        return Vec2(x * l, y * l);
    }

    inline Vec2 operator+(const Vec2& lhs, const Vec2& rhs)
    {
        return Vec2(lhs.x + rhs.x, lhs.y + rhs.y);
    }

    inline Vec2 operator-(const Vec2& lhs, const Vec2& rhs)
    {
        return Vec2(lhs.x - rhs.x, lhs.y - rhs.y);
    }

    inline Vec2 operator*(const Vec2& lhs, real_t s)
    {
        return Vec2(lhs.x * s, lhs.y * s);
    }

    inline Vec2 operator/(const Vec2& pt, real_t s)
    {
        return Vec2(pt.x / s, pt.y / s);
    }
}

#endif
