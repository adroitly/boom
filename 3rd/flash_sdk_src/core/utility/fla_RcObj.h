//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_RCOBJ_H__
#define __FLA_RCOBJ_H__

#include <memory>
#include "clover/IntrusiveObject.h"

namespace fla
{
    struct RcObj : public clover::IntrusiveObject<RcObj>
    {
    };
    typedef boost::intrusive_ptr<RcObj> RcObjPtr;

    template <typename T>
    struct RcWrapObj : public RcObj
    {
    public:
        static boost::intrusive_ptr<RcWrapObj> create();
        static boost::intrusive_ptr<RcWrapObj> create(const T& value);

        T val;

    private:
        RcWrapObj(const T& val_) : val(val_)
        {
        }

        RcWrapObj()
        {
        }
    };

    template <typename T>
    inline boost::intrusive_ptr<RcWrapObj<T>> RcWrapObj<T>::create()
    {
        return boost::intrusive_ptr<RcWrapObj>(new RcWrapObj(), false);
    }

    template <typename T>
    inline boost::intrusive_ptr<RcWrapObj<T>> RcWrapObj<T>::create(const T& value)
    {
        return boost::intrusive_ptr<RcWrapObj>(new RcWrapObj(value), false);
    }
}

#endif
