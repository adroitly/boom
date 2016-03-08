//=============================================================================
//  clover
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __CLOVER_REFCOUNTER_H__
#define __CLOVER_REFCOUNTER_H__

#include <cstdint>
#include <atomic>
#include <boost/noncopyable.hpp>

namespace clover
{
    class AtomicRefCounter : boost::noncopyable
    {
    public:
        AtomicRefCounter()
        {
            _refCount = 1;
        }

        int32_t add_fetch()
        {
            return _refCount.fetch_add(1) + 1;
        }

        int32_t sub_fetch()
        {
            return _refCount.fetch_sub(1) - 1;
        }

        int32_t fetch() const
        {
            return _refCount;
        }

    private:
        std::atomic<int32_t> _refCount;
    };

    class RefCounter : boost::noncopyable
    {
    public:
        RefCounter()
        {
            _refCount = 1;
        }

        int32_t add_fetch()
        {
            _refCount++;
            return _refCount;
        }

        int32_t sub_fetch()
        {
            _refCount--;
            return _refCount;
        }

        int32_t fetch() const
        {
            return _refCount;
        }

    private:
        int32_t _refCount;
    };
}

#endif