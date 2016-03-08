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

#ifndef __LIBRA_BITS_H__
#define __LIBRA_BITS_H__

namespace libra
{
    template <typename T, typename U>
    inline void bit_set(T* flags, U mask)
    {
        (*flags) |= mask;
    }

    template <typename T, typename U>
    inline void bit_clear(T* flags, U mask)
    {
        (*flags) &= ~mask;
    }

    template <typename T, typename U>
    inline void bit_set(T* flags, U mask, bool b)
    {
        if (b)
        {
            bit_set(flags, mask);
        }
        else
        {
            bit_clear(flags, mask);
        }
    }

    template <typename T, typename U>
    inline bool bit_test(T flags, U mask)
    {
        return (flags & mask) != 0;
    }
}

#endif
