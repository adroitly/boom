//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLABITMAPDATA_H__
#define __FLABITMAPDATA_H__

#include "FlaConfig.h"
#include "FlaEnum.h"

namespace fla
{
    class BitmapData;
}

class FlaBitmapData
{
public:
    FlaBitmapData();
    ~FlaBitmapData();
    FlaBitmapData(const FlaBitmapData& rhs);
    FlaBitmapData& operator=(const FlaBitmapData& rhs);

    FlaBitmapData(fla::BitmapData* impl);

    bool isNull() const;

    bool saveAsPng(const std::string& filePath) const;
    bool saveAsPngAsync(const std::string& filePath) const;

    int getWidth() const;
    int getHeight() const;
    int getContentWidth() const;
    int getContentHeight() const;

    cocos2d_bridge::Texture2D* transToTexture(FlaPixelFormat format) const;
    static cocos2d_bridge::Texture2D* loadPngTexture(const std::string& filePath, FlaPixelFormat format);

private:
    fla::BitmapData* _impl;
};

#endif
