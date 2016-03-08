//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_BATCHSTACK_H__
#define __FLA_BATCHSTACK_H__

#include "libra/libra_membuf.h"

namespace fla
{
    template <typename T>
    class BatchStack : boost::noncopyable
    {
    public:
        BatchStack()
        {
            membuf_init(&_stack, _buf, sizeof(_buf));
        }

        ~BatchStack()
        {
            membuf_finish(&_stack);
        }

        void push(const T& trans)
        {
            membuf_push(&_stack, &trans, sizeof(trans));
        }

        const T& top() const
        {
            auto size = membuf_size(&_stack);
            auto ptr = (T*)membuf_ptr(&_stack, size - sizeof(T));
            return *ptr;
        }

        void pop()
        {
            membuf_pop(&_stack, sizeof(T));
        }

        bool isUnique() const
        {
            return membuf_size(&_stack) == sizeof(T);
        }

        bool isEmpty() const
        {
            return membuf_size(&_stack) == 0;
        }

    private:
        libra_membuf _stack;
        char _buf[sizeof(T)];
    };
}

#endif
