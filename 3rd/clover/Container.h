//=============================================================================
//  clover
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __CLOVER_CONTAINER_H__
#define __CLOVER_CONTAINER_H__

#include <vector>
#include <map>
#include <algorithm>
#include "Traits.h"

namespace clover
{
    // 将符合条件的数据选出来
    template <typename ContainerT, typename Predicate>
    inline ContainerT select_if(const ContainerT& container, const Predicate& pred)
    {
        ContainerT result;
        std::copy_if(std::begin(container), std::end(container), std::back_inserter(result), pred);
        return result;
    }

    template <typename Key, typename Value, typename Predicate>
    inline std::vector<std::pair<Key, Value>> select_if(const std::map<Key, Value>& container, const Predicate& pred)
    {
        std::vector<std::pair<Key, Value>> result;
        std::copy_if(std::begin(container), std::end(container), std::back_inserter(result), pred);
        return result;
    }

    // 转换容器
    template <typename ContainerT, typename Fun>
    inline std::vector<typename function_traits<Fun>::result_type_remove_cv> transform(const ContainerT& container,
                                                                                       const Fun& fun)
    {
        typedef typename function_traits<Fun>::result_type_remove_cv RT;

        std::vector<RT> result;
        result.reserve(container.size());
        std::transform(std::begin(container), std::end(container), std::back_inserter(result), fun);
        return result;
    }

    template <typename ContainerT, typename Iterator, typename Fun>
    inline void transform(const ContainerT& container, Iterator iterator, const Fun& fun)
    {
        std::transform(std::begin(container), std::end(container), iterator, fun);
    }

    template <typename ContainerT, typename VT>
    inline bool has_value(ContainerT&& container, VT&& v)
    {
        auto iter = std::find(std::begin(container), std::end(container), v);
        return (iter != std::end(container));
    }

    template <typename ContainerT, typename VT>
    inline void erase_value(ContainerT&& container, VT&& v)
    {
        auto iter = std::find(std::begin(container), std::end(container), v);
        if (iter != std::end(container))
        {
            container.erase(iter);
        }
    }
}

#endif
