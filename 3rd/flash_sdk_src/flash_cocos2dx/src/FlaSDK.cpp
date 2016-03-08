//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "../FlaSDK.h"
#include "../FlaResourceCache.h"
#include "./fla_AsynManager.h"
#include "./fla_Settings.h"
#include "core/base/fla_utils.h"

namespace FlaSDK
{
    void purgeCachedData()
    {
        FlaResourceCache::getInstance().clear();
        fla::AsyncManager::getInstance().removeAllItems();
    }

    bool isAsyncManagerEmpty()
    {
        return fla::AsyncManager::getInstance().isEmpty();
    }

    void setTextureContentScaleFactor(float contentScale)
    {
        fla::settings::setTextureContentScale(contentScale);
    }

    float getTextureContentScaleFactor()
    {
        return fla::settings::getTextureContentScale();
    }

    void setReaderIgnorePlaceHolder(bool flag)
    {
        fla::settings::setReadIgnorePlaceHolde(flag);
    }

    std::string getKeyOfCache(const std::string& md5, int Id, float scale)
    {
        return fla::keyOfCache(md5, Id, 0, scale * getTextureContentScaleFactor(), 0);
    }

#if FLA_CHECK_AUTHORIZE
#include "../../authorize/authorize.h"
    void init(const std::string& secretID)
    {
        FlaAuthorize::initWithSecretID(secretID);
        fla::settings::setCheckAuthorizedFunc(FlaAuthorize::checkAuthorized);
    }
#endif
}
