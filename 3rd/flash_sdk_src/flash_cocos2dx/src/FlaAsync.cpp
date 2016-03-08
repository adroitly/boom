//=============================================================================
//  FlashFire
//
//  Copyright (C) 2014 AppleTreeBooks. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "../FlaAsync.h"
#include "./fla_AsynManager.h"

namespace FlaSDK
{
    namespace __detail
    {
        void async(const std::function<Any*()>& work, const std::function<void(Any*)>& callback)
        {
            fla::AsyncManager::getInstance().async(work, callback);
        }
    }

    void async(const std::function<void()>& work, const std::function<void()>& callback)
    {
        fla::AsyncManager::getInstance().async(work, callback);
    }
}
