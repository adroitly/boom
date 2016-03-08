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

#ifndef __META_TRAITS_H__
#define __META_TRAITS_H__

#include <tuple>

namespace meta
{
#define TYPE_HAS_MEM_SIGN(class_name, func)            \
    template <typename T, typename Sign>               \
    struct class_name                                  \
    {                                                  \
        typedef char yes;                              \
        typedef void* no;                              \
                                                       \
        template <typename U, U>                       \
        struct sign_check;                             \
                                                       \
        template <typename U>                          \
        static yes check(sign_check<Sign, &U::func>*); \
                                                       \
        template <typename>                            \
        static no check(...);                          \
                                                       \
        enum                                           \
        {                                              \
            value = sizeof(check<T>(0)) == sizeof(yes) \
        };                                             \
    };

#define TYPE_HAS_MEM_FUNC(class_name, func)            \
    template <typename T>                              \
    struct class_name                                  \
    {                                                  \
        typedef char yes;                              \
        typedef void* no;                              \
                                                       \
        template <typename C>                          \
        static yes check(decltype(&C::func));          \
        template <typename C>                          \
        static no check(...);                          \
                                                       \
    public:                                            \
        enum                                           \
        {                                              \
            value = sizeof(check<T>(0)) == sizeof(yes) \
        };                                             \
    };

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
}

#endif
