//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_Settings.h"
#include "cocos2d_bridge.h"
#include "../FlaConfig.h"

namespace fla
{
    namespace settings
    {
        static bool s_defaultCheckAuthorized()
        {
#if FLA_CHECK_AUTHORIZE
            return false;
#else
            return true;
#endif
        }

        static float s_contentScale = 0.0;
        static bool s_ignorePlaceHolde = false;
        static CheckAuthorizedFunc s_checkAuthroizedFunc = s_defaultCheckAuthorized;

        void setTextureContentScale(float contentScale)
        {
            s_contentScale = contentScale;
        }

        float getTextureContentScale()
        {
            if (s_contentScale == 0.0)
            {
                s_contentScale = cocos2d_bridge::Director_getInstance()->getContentScaleFactor();
            }
            return s_contentScale;
        }

        void setReadIgnorePlaceHolde(bool ignore)
        {
            s_ignorePlaceHolde = ignore;
        }

        bool getIgnorePlaceHolde()
        {
            return s_ignorePlaceHolde;
        }

        void setCheckAuthorizedFunc(CheckAuthorizedFunc func)
        {
            s_checkAuthroizedFunc = func;
        }

        CheckAuthorizedFunc getCheckAuthorizedFunc()
        {
            return s_checkAuthroizedFunc;
        }
    }

    cocos2d_bridge::Rect pixels_to_points(const cocos2d_bridge::Rect& rt)
    {
        auto result = rt;
        auto factor = 1.0 / settings::getTextureContentScale();
        result.origin.x *= factor;
        result.origin.y *= factor;
        result.size.width *= factor;
        result.size.height *= factor;
        return result;
    }
}
