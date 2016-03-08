//=============================================================================
//  clover
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __CLOVER_PTR_VECTOR_H__
#define __CLOVER_PTR_VECTOR_H__

#include <boost/noncopyable.hpp>
#include <type_traits>
#include <stdlib.h>
#include <assert.h>
#include <string.h>

namespace clover
{
    template <typename T>
    struct ptr_ref_policy
    {
        static T* assign(T* ptr)
        {
            ptr->retain();
            return ptr;
        }

        static void erase(T* ptr)
        {
            ptr->release();
        }
    };

    template <typename T>
    struct ptr_raw_policy
    {
        static T* assign(T* ptr)
        {
            return ptr;
        }

        static void erase(T*)
        {
        }
    };

    template <typename T, typename HoldePolicy = ptr_ref_policy<T>>
    class pod_ptr_vector : boost::noncopyable
    {
    public:
        void obj_init()
        {
            _size = 0;
            _capacity = 1;
            _u.ptr = nullptr;
        }

        void obj_finish()
        {
            clear();
            if (useVector())
            {
                free(_u.vector);
            }
        }

        size_t size() const
        {
            return _size;
        }

        bool empty() const
        {
            return _size == 0;
        }

        void clear()
        {
            for (auto ptr : *this)
            {
                HoldePolicy::erase(ptr);
            }
            _size = 0;
        }

        void reserve(size_t size)
        {
            recapacity(size);
        }

        void push_back(T* ptr);
        void pop_back();

        void insert(T** iter, T* ptr);
        void insert(size_t pos, T* ptr);

        void assign(T** iter, T* ptr);
        void assign(T** begin, T** end);

        void erase(T** iter);

        typedef T** iterator;
        typedef T** const_iterator;

        T* back()
        {
            assert(_size > 0);
            return begin()[_size - 1];
        }

        T* operator[](size_t idx)
        {
            assert(idx < _size);
            return begin()[idx];
        }

        const_iterator begin() const
        {
            return const_cast<pod_ptr_vector<T, HoldePolicy>*>(this)->begin();
        }

        const_iterator end() const
        {
            return const_cast<pod_ptr_vector<T, HoldePolicy>*>(this)->end();
        }

        iterator begin()
        {
            return useVector() ? _u.vector : &_u.ptr;
        }

        iterator end()
        {
            return begin() + _size;
        }

    private:
        bool useVector() const
        {
            return _capacity > 1;
        }
        void recapacity(size_t needSize);
        size_t adjust_apacity(size_t needSize);

    private:
        union
        {
            T* ptr;
            T** vector;
        } _u;
        size_t _size;
        size_t _capacity;
    };

    template <typename T, typename HoldePolicy>
    void pod_ptr_vector<T, HoldePolicy>::push_back(T* ptr)
    {
        if (useVector() || _size > 0)
        {
            recapacity(_size + 1);
            _u.vector[_size] = HoldePolicy::assign(ptr);
        }
        else
        {
            _u.ptr = HoldePolicy::assign(ptr);
        }
        _size++;
    }

    template <typename T, typename HoldePolicy>
    void pod_ptr_vector<T, HoldePolicy>::pop_back()
    {
        assert(_size > 0);
        auto ptr = back();
        HoldePolicy::erase(ptr);
        _size--;
    }

    template <typename T, typename HoldePolicy>
    void pod_ptr_vector<T, HoldePolicy>::insert(size_t pos, T* ptr)
    {
        assert(0 <= pos && pos <= _size);
        if (useVector() || _size > 0)
        {
            recapacity(_size + 1);
            auto iter_ptr = _u.vector + _size;
            auto iter_end = _u.vector + pos;

            while (iter_ptr > iter_end)
            {
                *iter_ptr = *(iter_ptr - 1);
                iter_ptr--;
            }
            *iter_end = HoldePolicy::assign(ptr);
        }
        else
        {
            _u.ptr = HoldePolicy::assign(ptr);
        }
        _size++;
    }

    template <typename T, typename HoldePolicy>
    inline void pod_ptr_vector<T, HoldePolicy>::insert(T** iter, T* ptr)
    {
        assert(begin() <= iter && iter <= end());
        insert(iter - begin(), ptr);
    }

    template <typename T, typename HoldePolicy>
    void pod_ptr_vector<T, HoldePolicy>::assign(T** iter, T* ptr)
    {
        assert(begin() <= iter && iter < end());
        HoldePolicy::erase(*iter);
        *iter = HoldePolicy::assign(ptr);
    }

    template <typename T, typename HoldePolicy>
    void pod_ptr_vector<T, HoldePolicy>::assign(T** begin, T** end)
    {
        assert(begin <= end);
        clear();
        reserve(end - begin);
        while (begin != end)
        {
            push_back(*begin);
            begin++;
        }
    }

    template <typename T, typename HoldePolicy>
    void pod_ptr_vector<T, HoldePolicy>::erase(T** iter)
    {
        assert(begin() <= iter && iter < end());
        if (useVector())
        {
            HoldePolicy::erase(*iter);
            // auto end = _u.vector + _size 有可能会崩
            auto end = _u.vector + _size - 1;
            while (iter != end)
            {
                *iter = *(iter + 1);
                iter++;
            }
        }
        else
        {
            assert(*iter == _u.ptr);
            HoldePolicy::erase(_u.ptr);
        }
        _size--;
    }

    template <typename T, typename HoldePolicy>
    size_t pod_ptr_vector<T, HoldePolicy>::adjust_apacity(size_t needSize)
    {
        assert(_capacity >= 1);
        size_t capacity = 0;
        if (_size == 0)
        {
            capacity = needSize;
        }
        else
        {
            capacity = _capacity * 2;
            assert(capacity > 0);
            while (capacity < needSize)
            {
                capacity *= 2;
            }
        }
        assert(capacity >= needSize);
        return capacity;
    }

    template <typename T, typename HoldePolicy>
    void pod_ptr_vector<T, HoldePolicy>::recapacity(size_t needSize)
    {
        assert(_capacity >= 1);
        if (_capacity >= needSize)
        {
            return;
        }

        size_t capacity = adjust_apacity(needSize);
        assert(capacity >= needSize);

        if (useVector())
        {
            T** newbuf = (T**)realloc(_u.vector, capacity * sizeof(T*));
            assert(newbuf);
            _u.vector = newbuf;
        }
        else
        {
            T** newbuf = (T**)malloc(capacity * sizeof(T*));
            assert(newbuf);
            *newbuf = _u.ptr;
            _u.vector = newbuf;
        }
        _capacity = capacity;
        assert(useVector());
    }

    static_assert(std::is_pod<pod_ptr_vector<int>>::value, "");

    template <typename T, typename HoldePolicy = ptr_ref_policy<T>>
    class ptr_vector : public pod_ptr_vector<T, HoldePolicy>
    {
    public:
        ptr_vector()
        {
            pod_ptr_vector<T, HoldePolicy>::obj_init();
        }

        ~ptr_vector()
        {
            pod_ptr_vector<T, HoldePolicy>::obj_finish();
        }

    private:
        void obj_init();
        void obj_finish();
    };
}

#endif
