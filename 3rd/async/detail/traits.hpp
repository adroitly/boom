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

#ifndef __ASYNC_TRAITS_H__
#define __ASYNC_TRAITS_H__

#include <tuple>

namespace async
{
    template <typename T>
    struct function_traits : public function_traits<decltype(&T::operator())>
    {
    };

    template <typename ReturnType, typename... Args>
    struct function_traits<ReturnType(Args...)>
    {
        enum
        {
            arity = sizeof...(Args)
        };
        enum
        {
            nargs = arity
        };
        typedef ReturnType result_type;
        typedef typename std::remove_cv<ReturnType>::type result_type_remove_cv;

        template <size_t i>
        struct arg
        {
            typedef typename std::tuple_element<i, std::tuple<Args...>>::type type;
        };
    };

    template <typename ClassType, typename ReturnType, typename... Args>
    struct function_traits<ReturnType (ClassType::*)(Args...) const> : public function_traits<ReturnType(Args...)>
    {
    };

    template <typename ReturnType, typename... Args>
    struct function_traits<ReturnType (*)(Args...)> : public function_traits<ReturnType(Args...)>
    {
    };

    template <typename ReturnType, typename... Args>
    struct function_traits<ReturnType(&)(Args...)> : public function_traits<ReturnType(Args...)>
    {
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
    struct SingleHolder
    {
        SingleHolder() : value()
        {
        }

        template <typename FunT>
        void toCall(const FunT& fun)
        {
            typedef Int2Type<function_traits<FunT>::nargs> Type;
            toCall(fun, Type());
        }

        template <typename FunT>
        void fromCall(const FunT& fun)
        {
            value = fun();
        }

    private:
        template <typename FunT>
        void toCall(const FunT& fun, Int2Type<0>)
        {
            fun();
        }

        template <typename FunT>
        void toCall(const FunT& fun, Int2Type<1>)
        {
            fun(value);
        }

        T value;
    };

    template <>
    struct SingleHolder<void>
    {
        template <typename FunT>
        void toCall(const FunT& fun)
        {
            fun();
        }

        template <typename FunT>
        void fromCall(const FunT& fun)
        {
            fun();
        }
    };
}

#endif
