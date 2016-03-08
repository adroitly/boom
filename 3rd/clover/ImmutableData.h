//=============================================================================
//  clover
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __CLOVER_IMMUTABLE_DATA_H__
#define __CLOVER_IMMUTABLE_DATA_H__

#include <cstdint>
#include <stddef.h>
#include <cassert>
#include <stdlib.h>
#include <memory>
#include <boost/noncopyable.hpp>

namespace clover
{
    struct MemCopy
    {
        static uint8_t* copy(const uint8_t* data, size_t size)
        {
            assert(data != nullptr);
            assert(size >= 0);
            uint8_t* tmp = (uint8_t*)malloc(size);
            assert(tmp);
            memcpy(tmp, data, size);
            return tmp;
        }
    };

    struct MemFree
    {
        static void free(uint8_t* data)
        {
            assert(data);
            ::free(data);
        }
    };

    template <typename T>
    struct MemDelete
    {
        static void free(uint8_t* data)
        {
            assert(data);
            delete data;
        }
    };

    template <typename T>
    struct MemDelete<T[]>
    {
        static void free(uint8_t* data)
        {
            assert(data);
            delete[] data;
        }
    };

    struct MemNull
    {
        static uint8_t* copy(const uint8_t* data, size_t size)
        {
            (void)data;
            (void)size;
            assert(data != nullptr);
            assert(size >= 0);
            return (uint8_t*)data;
        }

        static void free(uint8_t* data)
        {
            (void)data;
            assert(data);
            // donothing
        }
    };

    template <typename CopyPolicy, typename FreePolicy>
    class ImmutableData final : boost::noncopyable
    {
    public:
        ImmutableData()
        {
            _data = nullptr;
            _size = 0;
        }

        ImmutableData(const void* data, size_t size)
        {
            assgin(data, size);
        }

        ImmutableData(ImmutableData&& rhs)
        {
            _data = rhs._data;
            _size = rhs._size;
            rhs._data = nullptr;
            rhs._size = 0;
        }

        ~ImmutableData()
        {
            safe_free();
        }

        void reset(const void* data, size_t size)
        {
            safe_free();
            assgin(data, size);
        }

        void clear()
        {
            reset(nullptr, 0);
        }

        const uint8_t* data() const
        {
            return _data;
        }

        size_t size() const
        {
            return _size;
        }

        const uint8_t* begin() const
        {
            return _data;
        }

        const uint8_t* end() const
        {
            return _data + _size;
        }

        uint8_t front() const
        {
            return _data[0];
        }

        uint8_t back() const
        {
            return _data[_size - 1];
        }

        bool empty() const
        {
            return _size == 0;
        }

        uint8_t operator[](size_t idx) const
        {
            return _data[idx];
        }

    private:
        void safe_free();
        void assgin(const void* data, size_t size);

    private:
        uint8_t* _data;
        size_t _size;
    };

    template <typename CopyPolicy, typename FreePolicy>
    void ImmutableData<CopyPolicy, FreePolicy>::assgin(const void* data, size_t size)
    {
        // 不能写成下面的形式
        // if (data == nullptr || size == 0)
        // 因为有时候，传进来的size == 0, 而data不为空
        if (data == nullptr)
        {
            _data = nullptr;
            _size = 0;
        }
        else
        {
            _data = CopyPolicy::copy((uint8_t*)data, size);
            _size = size;
        }
    }

    template <typename CopyPolicy, typename FreePolicy>
    void ImmutableData<CopyPolicy, FreePolicy>::safe_free()
    {
        if (_data != nullptr)
        {
            FreePolicy::free(_data);
        }
    }
}

#endif
