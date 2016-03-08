//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLACONFIG_H__
#define __FLACONFIG_H__

#include "cocos2d.h"

#ifndef FLA_CHECK_AUTHORIZE
#define FLA_CHECK_AUTHORIZE 0
#endif

namespace cocos2d_bridge
{
#if COCOS2D_VERSION >= 0x00030000
    typedef cocos2d::Texture2D      Texture2D;
    typedef cocos2d::SpriteFrame    SpriteFrame;
    typedef cocos2d::BlendFunc      BlendFunc;
    typedef cocos2d::Color4F        Color4F;
    typedef cocos2d::Color3B        Color3B;
    typedef cocos2d::Node           NodeRGBA;
    typedef cocos2d::Rect           Rect;
    typedef cocos2d::Size           Size;
    typedef cocos2d::Vec2           Point;
    typedef cocos2d::Ref            Object;
    typedef cocos2d::__Dictionary   Dictionary;
    typedef cocos2d::AffineTransform AffineTransform;
#else
    typedef cocos2d::CCTexture2D    Texture2D;
    typedef cocos2d::CCSpriteFrame  SpriteFrame;
    typedef cocos2d::ccBlendFunc    BlendFunc;
    typedef cocos2d::ccColor4F      Color4F;
    typedef cocos2d::ccColor3B      Color3B;
    typedef cocos2d::CCNodeRGBA     NodeRGBA;
    typedef cocos2d::CCRect         Rect;
    typedef cocos2d::CCSize         Size;
    typedef cocos2d::CCPoint        Point;
    typedef cocos2d::CCObject       Object;
    typedef cocos2d::CCDictionary   Dictionary;
    typedef cocos2d::CCAffineTransform AffineTransform;
#endif
}

#endif
