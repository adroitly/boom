//=============================================================================
//  clover
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __CLOVER_LEXICAL_CAST_H__
#define __CLOVER_LEXICAL_CAST_H__

#include <string>
#include <stdlib.h>
#include "Traits.h"

namespace clover
{
    inline const std::string& to_string(const std::string& str)
    {
        return str;
    }

    inline std::string to_string(const char* str)
    {
        return str;
    }

    namespace detail
    {
        // can't use std::to_string. Andoid no std::to_string function
        template <typename T>
        inline std::string to_string_format(T val, const char* format)
        {
            char buf[64];
            sprintf(buf, format, val);
            return buf;
        }

        inline std::string to_string(int val)
        {
            return to_string_format(val, "%d");
        }

        inline std::string to_string(double val)
        {
            return to_string_format(val, "%lf");
        }

        inline std::string to_string(float val)
        {
            return to_string_format(val, "%f");
        }

        inline std::string to_string(long val)
        {
            return to_string_format(val, "%ld");
        }

        template <typename T>
        inline std::string to_string_check_enum(T value, Int2Type<false>)  // 非枚举
        {
            return detail::to_string(value);
        }

        template <typename T>
        inline std::string to_string_check_enum(T value, Int2Type<true>)  // 枚举
        {
            return detail::to_string(static_cast<int>(value));
        }
    }

    template <typename T>
    inline std::string to_string(T value)
    {
        return detail::to_string_check_enum(value, Int2Type<std::is_enum<T>::value>());
    }

    namespace detail
    {
        inline int from_string(const char* str, Type2Type<int>)
        {
            return atoi(str);
        }

        inline int from_string(const char* str, Type2Type<double>)
        {
            return atof(str);
        }

        inline int from_string(const char* str, Type2Type<float>)
        {
            return atof(str);
        }

        inline long from_string(const char* str, Type2Type<long>)
        {
            return atol(str);
        }

        template <typename T>
        inline T from_string_check_enum(const char* str, Int2Type<false>)  // 非枚举
        {
            return from_string(str, Type2Type<T>());
        }

        template <typename T>
        inline T from_string_check_enum(const char* str, Int2Type<true>)  // 枚举
        {
            return static_cast<T>(atoi(str));
        }
    }

    template <typename T>
    inline T from_string(const char* str)
    {
        return detail::from_string_check_enum<T>(str, Int2Type<std::is_enum<T>::value>());
    }

    template <typename T>
    inline T from_string(const std::string& str)
    {
        return from_string<T>(str.c_str());
    }
}

#endif
