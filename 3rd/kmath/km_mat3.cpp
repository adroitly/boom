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

#include "km_mat3.h"

namespace km
{
    void Mat3::rotate(real_t angle)
    {
        auto fSin = std::sin(angle);
        auto fCos = std::cos(angle);

        auto tmpA = a * fCos + c * fSin;
        auto tmpB = b * fCos + d * fSin;
        auto tmpC = c * fCos - a * fSin;
        auto tmpD = d * fCos - b * fSin;

        a = tmpA;
        b = tmpB;
        c = tmpC;
        d = tmpD;
    }

    Mat3 Mat3::lerp(const Mat3& lhs, const Mat3& rhs, real_t ratio)
    {
        Mat3 trans;
        trans.a = s_lerp(lhs.a, rhs.a, ratio);
        trans.b = s_lerp(lhs.b, rhs.b, ratio);
        trans.c = s_lerp(lhs.c, rhs.c, ratio);
        trans.d = s_lerp(lhs.d, rhs.d, ratio);
        trans.tx = s_lerp(lhs.tx, rhs.tx, ratio);
        trans.ty = s_lerp(lhs.ty, rhs.ty, ratio);
        return trans;
    }

    Mat3 operator*(const Mat3& lhs, const Mat3& rhs)
    {
        Mat3 m;
        m.a = dotMult(lhs.a, lhs.c, rhs.a, rhs.b);
        m.b = dotMult(lhs.b, lhs.d, rhs.a, rhs.b);
        m.c = dotMult(lhs.a, lhs.c, rhs.c, rhs.d);
        m.d = dotMult(lhs.b, lhs.d, rhs.c, rhs.d);
        m.tx = dotMult(lhs.a, lhs.c, rhs.tx, rhs.ty) + lhs.tx;
        m.ty = dotMult(lhs.b, lhs.d, rhs.tx, rhs.ty) + lhs.ty;
        return m;
    }

    Rect2 operator*(const Mat3& lhs, const Rect2& rect)
    {
        Vec2 minPt = lhs * Vec2(rect.x, rect.y);
        Vec2 maxPt = lhs * Vec2(rect.getMaxX(), rect.getMaxY());

        if (minPt.x > maxPt.x)
        {
            std::swap(minPt.x, maxPt.x);
        }

        if (minPt.y > maxPt.y)
        {
            std::swap(minPt.y, maxPt.y);
        }

        return Rect2(minPt.x, minPt.y, maxPt.x - minPt.x, maxPt.y - minPt.y);
    }

    void Mat3::invert()
    {
        Mat3 t = *this;
        auto determinant = 1.0 / (t.a * t.d - t.b * t.c);
        a = determinant * t.d;
        b = -determinant * t.b;
        c = -determinant * t.c;
        d = determinant * t.a;
        tx = determinant * (t.c * t.ty - t.d * t.tx);
        ty = determinant * (t.b * t.tx - t.a * t.ty);
    }
}
