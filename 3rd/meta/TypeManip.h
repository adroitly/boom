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

#ifndef __META_TYPEMANIP_H__
#define __META_TYPEMANIP_H__

namespace meta
{
    template <bool v>
    struct check
    {
    };
    typedef check<true> true_type;
    typedef check<false> false_type;

    template <>
    struct check<false>
    {
        typedef false_type type;
    };

    template <int v>
    struct Int2Type
    {
        enum
        {
            value = v
        };
    };

    template <typename T>
    struct Type2Type
    {
        typedef T type;
    };

    template <bool flag, typename T, typename U>
    struct TypeIfElse
    {
        typedef T type;
    };

    template <typename T, typename U>
    struct TypeIfElse<false, T, U>
    {
        typedef U type;
    };

    struct EmptyType
    {
    };
}

#endif
