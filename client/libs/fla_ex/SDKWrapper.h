//
//  FlaSDKWrapper.h
//  Game
//
//  Created by HJC on 14-1-10.
//
//

#ifndef __FLASDKWRAPPER_H__
#define __FLASDKWRAPPER_H__

#include "FlaSDK.h"

namespace fla_ex
{
    FlaCacheStrategy* getGlobalCacheStrategy(FlaPixelFormat pixelFormat);
    FlaCollection getCollection(const std::string& binName);
};

#endif
