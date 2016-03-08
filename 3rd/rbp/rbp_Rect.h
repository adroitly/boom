/** @file Rect.h
 @author Jukka Jylänki

 This work is released to Public Domain, do whatever you want with it.
 */
#ifndef __RBP_RECT_H__
#define __RBP_RECT_H__

#include <vector>
#include <cassert>
#include <cstdlib>

namespace rbp
{
    struct RectSize
    {
        int width;
        int height;
    };

    inline RectSize RectSizeMake(int width, int height)
    {
        RectSize size = { width, height };
        return size;
    }

    struct Rect
    {
        int x;
        int y;
        int width;
        int height;
    };

    /// Returns true if a is contained in b.
    bool IsContainedIn(const Rect& a, const Rect& b);
}

#endif
