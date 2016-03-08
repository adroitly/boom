//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_BITMAPDATA_H__
#define __FLA_BITMAPDATA_H__

#include <memory>
#include "clover/IntrusiveObject.h"

namespace fla
{
    enum class PixelFormat
    {
        RGBA8888    =   0,   // 32 Bit
        RGBA4444    =   1,   // 16 Bit
        ARGB4444    =   2,   // 16 Bit
    };
    
    class BitmapData : public clover::IntrusiveObject<BitmapData>
    {
    public:
        static Ptr create(int width, int height, PixelFormat pixelFormat);
        static Ptr create(void* pixels, bool copyPixels, int width, int height, PixelFormat pixelFormat);
        
        ~BitmapData();
        
        void* getPixels() const         {   return _pixels;     }
        size_t getPixelLength() const;
        
        int   getWidth() const          {   return _width;      }
        int   getHeight() const         {   return _height;     }
        
        void  setContentSize(int width, int height);
        
        int  getContentWidth() const    {   return _contentWidth;   }
        int  getContentHeight() const   {   return _contentHeight;  }
        
        PixelFormat getPixelFormat() const  {   return _pixelFormat;    }
        BitmapData::Ptr changePixelFormat(PixelFormat pixelFormat) const;
        
        bool isFormat8888() const;
        bool isFormat4444() const;
        
    private:
        BitmapData(int width, int height, PixelFormat pixelFormat);
        BitmapData(void* pixels, bool copyPixels, int width, int height, PixelFormat pixelFormat);
        BitmapData();
        BitmapData::Ptr copyBitmapData(void* pixel, PixelFormat pixelFormat) const;
        
    private:
        void*       _pixels;
        int         _width;
        int         _height;
        int         _contentWidth;
        int         _contentHeight;
        PixelFormat _pixelFormat;
        bool        _needFreePixels;
    };
}


#endif
