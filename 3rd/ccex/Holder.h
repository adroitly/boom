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

#ifndef __CCEX_CCHOLDER_H__
#define __CCEX_CCHOLDER_H__

#include "ccex_Config.h"
#include <tuple>

namespace ccex
{
    // 用于存放任何数
    template <typename T, typename... Args>
    class Holder : public Object
    {
    public:
        static Holder* create(const T& value, const Args&... args)
        {
            auto holder = new Holder(value, args...);
            holder->autorelease();
            return holder;
        }

        typedef std::tuple<T, Args...> tuple_type;

        template <int N>
        const typename std::tuple_element<N, tuple_type>::type& get() const
        {
            return std::get<N>(_tuple);
        }

        const typename std::tuple_element<0, tuple_type>::type& getValue() const
        {
            static_assert(std::tuple_size<tuple_type>::value == 1, "");
            return get<0>();
        }

    private:
        explicit Holder(const T& value, const Args&... args) : _tuple(value, args...)
        {
        }
        tuple_type _tuple;
    };

    template <typename T, typename... Args>
    inline Holder<T, Args...>* CCHolderMake(const T& value, const Args&... args)
    {
        return Holder<T, Args...>::create(value, args...);
    }

    template <typename T, typename... Args>
    inline Holder<T, Args...>* CCHolderCast(Object* obj)
    {
        return static_cast<Holder<T, Args...>*>(obj);
    }
}

#endif
