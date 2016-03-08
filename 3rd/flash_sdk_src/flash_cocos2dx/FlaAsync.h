//=============================================================================
//  FlashFire
//
//  Copyright (C) 2014 AppleTreeBooks. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLAASYNC_H__
#define __FLAASYNC_H__

#include <functional>

namespace FlaSDK
{
    namespace __detail
    {
        struct Any
        {
            virtual ~Any()  {}
        };

        template <typename T>
        struct AnyWrap : public Any
        {
            AnyWrap(const T& val_) : val(val_)  {}
            T val;
        };

        void async(const std::function<Any*()>& work, const std::function<void(Any*)>& callback);
    }

    // 异步执行函数
    template <typename T, typename Fun>
    void async(const std::function<T()>& work, const Fun& callback)
    {
        __detail::async(
            [=]
            {
                return new __detail::AnyWrap<T>(work());
            },
            [=](__detail::Any* any)
            {
                auto wrap = static_cast<__detail::AnyWrap<T>*>(any);
                callback(wrap->val);
                delete wrap;
            });
    }

    void async(const std::function<void()>& work, const std::function<void()>& callback);
}

#endif
