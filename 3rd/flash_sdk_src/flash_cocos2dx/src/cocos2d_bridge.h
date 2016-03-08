//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __COCOS2D_BRIDGE_H__
#define __COCOS2D_BRIDGE_H__

#include "../FlaConfig.h"

#if COCOS2D_VERSION >= 0x00030000
#include "./cocos2d_bridge_3x.h"
#else
#include "./cocos2d_bridge_2x.h"
#endif

namespace cocos2d_bridge
{
    bool loadFramesWithPlistFile(const std::string& path, uint64_t textureId);
    bool loadFramesWithLuaFile(const std::string& path, uint64_t textureId);
}

#endif