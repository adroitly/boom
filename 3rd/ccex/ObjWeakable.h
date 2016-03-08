/*
 The MIT License (MIT)
 
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

#ifndef __CCEX_OBJWEAKABLE_H__
#define __CCEX_OBJWEAKABLE_H__

#include "cocos2d.h"

namespace ccex
{
    typedef cocos2d::Ref Object;

    namespace weak_detail
    {
        typedef uint64_t unique_id;
        inline unique_id weaktable_nullId()
        {
            return 0;
        }
        unique_id weaktable_add(cocos2d::Ref* obj);
        void weaktable_remove(const unique_id& Id);
        cocos2d::Ref* weaktable_lock(const unique_id& Id);
    }

    template <typename T>
    class ObjWeakable;

    template <typename T>
    class ObjWeakId
    {
    public:
        ObjWeakId() : _Id(weak_detail::weaktable_nullId())
        {
        }

        template <typename U>
        explicit ObjWeakId(const ObjWeakId<U>& rhs)
            : _Id(rhs.getRawId())
        {
        }

        template <typename U>
        ObjWeakId& operator=(const ObjWeakId<U>& rhs)
        {
            _Id = rhs.getRawId();
            return *this;
        }

        T* lock() const
        {
            return (T*)(weak_detail::weaktable_lock(_Id));
        }

        const weak_detail::unique_id& getRawId() const
        {
            return _Id;
        }

        bool operator<(const ObjWeakId<T>& rhs) const
        {
            return getRawId() < rhs.getRawId();
        }

        bool operator==(const ObjWeakId<T>& rhs) const
        {
            return getRawId() == rhs.getRawId();
        }

        bool operator!=(const ObjWeakId<T>& rhs) const
        {
            return getRawId() != rhs.getRawId();
        }

    private:
        friend ObjWeakable<T>;
        weak_detail::unique_id _Id;
    };

    template <typename T>
    class ObjWeakable
    {
    public:
        typedef ObjWeakId<T> WeakIdType;

        // Noncopyable
        ObjWeakable(const ObjWeakable&) = delete;
        const ObjWeakable& operator=(const ObjWeakable&) = delete;

        explicit ObjWeakable()
        {
            static_assert(std::is_base_of<Object, T>::value, "");
            T* obj = static_cast<T*>(this);
            _Id._Id = weak_detail::weaktable_add(obj);
        }

        ~ObjWeakable()
        {
            weak_detail::weaktable_remove(_Id._Id);
        }

        ObjWeakId<T> getWeakId() const
        {
            return _Id;
        }

    private:
        ObjWeakId<T> _Id;
    };
}

#endif
