//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_COCOS2D_TEXTURE__
#define __FLA_COCOS2D_TEXTURE__

#include "cocos2d.h"
#include "../FlaConfig.h"
#include "../../core/definition/fla_Definition.h"
#include "../../core/base/fla_BitmapData.h"

namespace fla
{
    BitmapData::Ptr transToBitmapData(const Definition::Ptr& define, float scale, float ratio, PixelFormat format);
    BitmapData::Ptr loadBitmapFromPngFile(const std::string& filePath, PixelFormat format);
    bool saveBitmapToPngFile(const BitmapData::Ptr& bitmapData, const std::string& filePath);
    cocos2d_bridge::Texture2D* definition_transToTexture(Definition* definition, float scale, float ratio, PixelFormat format);
    cocos2d_bridge::Texture2D* bitmap_transToTexture(const BitmapData::Ptr& bitmapData, PixelFormat format);
    cocos2d_bridge::Texture2D* texture_loadPngFromFile(const std::string& filePath, PixelFormat format);
}

#endif
