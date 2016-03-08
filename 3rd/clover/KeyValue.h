//=============================================================================
//  clover
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __CLOVER_KEYVALUE_H__
#define __CLOVER_KEYVALUE_H__

#include <iterator>
#include <cstring>

namespace clover
{
    namespace keyvalue_details
    {
        // 判断是否相等
        template <typename Key1, typename Key2>
        inline bool isEqual(Key1&& key1, Key2&& key2)
        {
            return key1 == key2;
        }

        inline bool isEqual(const char* key1, const char* key2)
        {
            return strcmp(key1, key2) == 0;
        }
    }

    template <typename RangeT, typename Key, typename Value>
    auto keyvalue_map(RangeT&& range, Key&& key, Value&& defaultV) -> decltype(std::begin(range)->value)
    {
        for (auto& iter : range)
        {
            if (keyvalue_details::isEqual(iter.key, key))
            {
                return iter.value;
            }
        }
        return defaultV;
    }
}

#endif
