//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_REF_H__
#define __FLA_REF_H__

#include "clover/IntrusiveObject.h"
#include "fla_Base.h"

#if FLA_USE_LUA_BINDING
#include "cocos2d.h"
#include "libra/libra_atomic.h"
#endif

namespace fla
{
#if FLA_USE_LUA_BINDING

    template <typename DerivedT>
    class Ref : public cocos2d::Ref
    {
    public:
        typedef boost::intrusive_ptr<DerivedT> Ptr;

        bool isUnique() const
        {
            return getReferenceCount() == 1;
        }

        void retain()
        {
            libra_atomic_increment(&_referenceCount);
        }

        void release()
        {
            if (libra_atomic_decrement(&_referenceCount) == 0)
            {
                delete this;
            }
        }
    };

    template <typename DerivedT>
    inline void intrusive_ptr_add_ref(Ref<DerivedT>* obj)
    {
        obj->retain();
    }

    template <typename DerivedT>
    inline void intrusive_ptr_release(Ref<DerivedT>* obj)
    {
        obj->release();
    }

#else

    template <typename DerivedT>
    class Ref : public clover::IntrusiveObject<DerivedT>
    {
    };

#endif

    template <typename T, typename... Args>
    inline boost::intrusive_ptr<T> makeRef(Args&&... args)
    {
        return boost::intrusive_ptr<T>(new T(std::forward<Args>(args)...), false);
    }
}

#endif
