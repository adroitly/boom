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

#ifndef __KM_MAT3_H__
#define __KM_MAT3_H__

#include "km_types.h"
#include "km_vec2.h"
#include "km_rect2.h"

namespace km
{
    class Mat3 final
    {
    public:
        real_t a, b;
        real_t c, d;
        real_t tx, ty;

        Mat3()
        {
            set(1, 0, 0, 1, 0, 0);
        }

        Mat3(real_t a_, real_t b_, real_t c_, real_t d_, real_t tx_, real_t ty_)
        {
            a = a_;
            b = b_;
            c = c_;
            d = d_;
            tx = tx_;
            ty = ty_;
        }

        void set(real_t a_, real_t b_, real_t c_, real_t d_, real_t tx_, real_t ty_)
        {
            a = a_;
            b = b_;
            c = c_;
            d = d_;
            tx = tx_;
            ty = ty_;
        }

        template <typename U>
        void get(U& a_, U& b_, U& c_, U& d_, U& tx_, U& ty_) const
        {
            a_ = a;
            b_ = b;
            c_ = c;
            d_ = d;
            tx_ = tx;
            ty_ = ty;
        }

        static Mat3 lerp(const Mat3& lhs, const Mat3& rhs, real_t ratio);

        static Mat3 makeIdentity()
        {
            return Mat3(1, 0, 0, 1, 0, 0);
        }

        static Mat3 makeTranslation(real_t tx, real_t ty)
        {
            return Mat3(1, 0, 0, 1, tx, ty);
        }

        static Mat3 makeScale(real_t sx, real_t sy)
        {
            return Mat3(sx, 0, 0, sy, 0, 0);
        }

        static Mat3 makeScale(real_t s)
        {
            return makeScale(s, s);
        }

        static Mat3 makeRotation(real_t angle)
        {
            auto cosA = std::cos(angle);
            auto sinA = std::sin(angle);
            return Mat3(cosA, sinA, -sinA, cosA, 0, 0);
        }

        static Mat3 matrixScale(const Mat3& matrix, real_t s);

        void scale(real_t sx, real_t sy);
        void rotate(real_t angle);
        void translate(real_t tx, real_t ty);
        void invert();

        real_t computeScaleX() const;
        real_t computeScaleY() const;
        real_t computeRotation() const;
        bool isXFlip() const;
    };

    /////////////////////////////////////////////////////////////////////////////////
    inline void Mat3::scale(real_t sx, real_t sy)
    {
        a *= sx;
        b *= sx;
        c *= sy;
        d *= sy;
    }

    inline void Mat3::translate(real_t tx_, real_t ty_)
    {
        tx += dotMult(a, c, tx_, ty_);
        ty += dotMult(b, d, tx_, ty_);
    }

    inline bool Mat3::isXFlip() const
    {
        return a * d < 0;
    }

    inline real_t Mat3::computeScaleX() const
    {
        return std::sqrt(a * a + c * c);
    }

    inline real_t Mat3::computeScaleY() const
    {
        return std::sqrt(b * b + d * d);
    }

    inline real_t Mat3::computeRotation() const
    {
        return std::atan(b / d);
    }

    Mat3 operator*(const Mat3& lhs, const Mat3& rhs);

    inline Vec2 operator*(const Mat3& lhs, const Vec2& pt)
    {
        auto x = dotMult(lhs.a, lhs.c, pt.x, pt.y) + lhs.tx;
        auto y = dotMult(lhs.b, lhs.d, pt.x, pt.y) + lhs.ty;
        return Vec2(x, y);
    }

    Rect2 operator*(const Mat3& lhs, const Rect2& rect);

    inline Mat3 Mat3::matrixScale(const Mat3& matrix, real_t scale)
    {
        return matrix * Mat3::makeScale(scale);
    }

    inline bool operator==(const Mat3& lhs, const Mat3& rhs)
    {
        return memcmp(&lhs, &rhs, sizeof(lhs)) == 0;
    }
}

#endif
