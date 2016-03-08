//=============================================================================
//  clover
//
//  Copyright (C) 2015 HJC. All rights reserved.
//
//  hjcapple@gmail.com
//
//=============================================================================

#ifndef __CLOVER_INTRUSIVEOBJECT_H__
#define __CLOVER_INTRUSIVEOBJECT_H__

#include <boost/intrusive_ptr.hpp>
#include <boost/noncopyable.hpp>
#include "./RefCounter.h"

namespace clover
{
    template <typename DerivedT, typename RefCounterT = clover::AtomicRefCounter>
    class IntrusiveObject : boost::noncopyable
    {
    public:
        typedef boost::intrusive_ptr<DerivedT> Ptr;

        virtual ~IntrusiveObject()
        {
        }

        void retain()
        {
            _refCounter.add_fetch();
        }

        void release()
        {
            if (_refCounter.sub_fetch() == 0)
            {
                delete this;
            }
        }

        bool isUnique() const
        {
            return _refCounter.fetch() == 1;
        }

    private:
        RefCounterT _refCounter;
    };

    ////////////////////////////////////////////////////////
    template <typename DerivedT>
    inline void intrusive_ptr_add_ref(DerivedT* obj)
    {
        obj->retain();
    }

    template <typename DerivedT>
    inline void intrusive_ptr_release(DerivedT* obj)
    {
        obj->release();
    }

    template <typename DerivedT>
    inline void intrusive_ptr_safe_retain(DerivedT* obj)
    {
        if (obj)
        {
            obj->retain();
        }
    }

    template <typename DerivedT>
    inline void intrusive_ptr_safe_release(DerivedT* obj)
    {
        if (obj)
        {
            obj->release();
        }
    }

    template <typename T>
    inline void intrusive_ptr_safe_assign(T*& lhs, T* rhs)
    {
        if (lhs != rhs)
        {
            intrusive_ptr_safe_release(lhs);
            lhs = rhs;
            intrusive_ptr_safe_retain(lhs);
        }
    }
}

#endif