//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_SETTINGS_H__
#define __FLA_SETTINGS_H__

#include "cocos2d.h"
#include "cocos2d_bridge.h"

namespace fla
{
    namespace settings
    {
        typedef bool (*CheckAuthorizedFunc)();

        void setTextureContentScale(float contentScale);
        float getTextureContentScale();

        void setReadIgnorePlaceHolde(bool ignore);
        bool getIgnorePlaceHolde();

        void setCheckAuthorizedFunc(CheckAuthorizedFunc func);
        CheckAuthorizedFunc getCheckAuthorizedFunc();
    }

    cocos2d_bridge::Rect pixels_to_points(const cocos2d_bridge::Rect& rt);
}

#endif
