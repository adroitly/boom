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

#include "km_rect2.h"

namespace km
{
    bool Rect2::isSeparated(const Rect2& rect) const
    {
        if (getMaxX() < rect.x)
        {
            return true;
        }

        if (getMaxY() < rect.y)
        {
            return true;
        }

        if (rect.getMaxX() < x)
        {
            return true;
        }

        if (rect.getMaxY() < y)
        {
            return true;
        }

        return false;
    }

    void Rect2::unionRect(const Rect2& rect)
    {
        auto thisLeftX = x;
        auto thisRightX = x + width;
        auto thisTopY = y + height;
        auto thisBottomY = y;

        if (thisRightX < thisLeftX)
        {
            std::swap(thisRightX, thisLeftX);  // This rect has negative width
        }

        if (thisTopY < thisBottomY)
        {
            std::swap(thisTopY, thisBottomY);  // This rect has negative height
        }

        auto otherLeftX = rect.x;
        auto otherRightX = rect.x + rect.width;
        auto otherTopY = rect.y + rect.height;
        auto otherBottomY = rect.y;

        if (otherRightX < otherLeftX)
        {
            std::swap(otherRightX, otherLeftX);  // Other rect has negative width
        }

        if (otherTopY < otherBottomY)
        {
            std::swap(otherTopY, otherBottomY);  // Other rect has negative height
        }

        auto combinedLeftX = std::min(thisLeftX, otherLeftX);
        auto combinedRightX = std::max(thisRightX, otherRightX);
        auto combinedTopY = std::max(thisTopY, otherTopY);
        auto combinedBottomY = std::min(thisBottomY, otherBottomY);

        this->set(combinedLeftX, combinedBottomY, combinedRightX - combinedLeftX, combinedTopY - combinedBottomY);
    }
}