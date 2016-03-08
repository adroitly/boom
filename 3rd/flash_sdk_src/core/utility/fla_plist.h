//=============================================================================
//  clover
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __CLOVER_PLIST_H__
#define __CLOVER_PLIST_H__

#include "./fla_Value.h"

namespace clover
{
    namespace plist
    {
        typedef clover::ValueType ValueType;
        typedef clover::Value Value;

        std::string valueToPlistString(const Value& value);
    }
}

#endif
