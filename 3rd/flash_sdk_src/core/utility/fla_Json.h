//=============================================================================
//  clover
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __CLOVER_JSON_H__
#define __CLOVER_JSON_H__

#include "./fla_Value.h"

namespace clover
{
    namespace json
    {
        typedef clover::ValueType ValueType;
        typedef clover::Value Value;

        std::string valueToString(const Value& value);
        Value stringToValue(const std::string& str);
        Value stringToValue(const char* str, size_t len);
    }
}

#endif
