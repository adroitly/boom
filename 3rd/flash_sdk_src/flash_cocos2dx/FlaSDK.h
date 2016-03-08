//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLASDK_H__
#define __FLASDK_H__

#include "FlaCollection.h"
#include "FlaMovieNode.h"
#include "FlaDefinition.h"
#include "FlaEnum.h"
#include "FlaCacheStrategy.h"
#include "FlaResourceCache.h"
#include "FlaTexturePackage.h"
#include "FlaGLProgram.h"
#include "FlaAsync.h"

namespace FlaSDK
{
#if FLA_CHECK_AUTHORIZE
    void init(const std::string& secretID);
#endif

    // 清除FlashSDK所用到的资源
    void purgeCachedData();
    bool isAsyncManagerEmpty();

    std::string getKeyOfCache(const std::string& md5, int Id, float scale);

    void setTextureContentScaleFactor(float contentScale);
    float getTextureContentScaleFactor();

    void setReaderIgnorePlaceHolder(bool flag);
};

#endif
