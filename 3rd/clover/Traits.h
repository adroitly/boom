//=============================================================================
//  clover
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __CLOVER_TRAITS_H__
#define __CLOVER_TRAITS_H__

#include <type_traits>
#include <tuple>

namespace clover
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
    struct Type2Type
    {
        typedef T type;
    };
}

#endif
