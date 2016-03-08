//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================
#include "../../base/fla_Base.h"
#if (FLA_TARGET_PLATFORM == FLA_PLATFORM_MAC) || (FLA_TARGET_PLATFORM == FLA_PLATFORM_IOS)

#include "fla_QuartzImage.h"
#include <CoreFoundation/CoreFoundation.h>
#include <ImageIO/ImageIO.h>
#include "fla_CFScopeRelease.h"

namespace fla
{
    static void writePNGToFile(CGImageRef image, const std::string& filePath)
    {
        CFStringRef path = CFStringCreateWithCString(NULL, filePath.c_str(), kCFStringEncodingUTF8);
        CF_SCOPE_RELEASE(path);

        CFStringRef typepng = CFStringCreateWithCString(NULL, "public.png", kCFStringEncodingUTF8);
        CF_SCOPE_RELEASE(typepng);

        CFURLRef url = CFURLCreateWithFileSystemPath(NULL, path, kCFURLPOSIXPathStyle, false);
        CF_SCOPE_RELEASE(url);

        CGImageDestinationRef destination = CGImageDestinationCreateWithURL(url, typepng, 1, NULL);
        CF_SCOPE_RELEASE(destination);

        CGImageDestinationAddImage(destination, image, nil);

        if (!CGImageDestinationFinalize(destination))
        {
        }
    }

    CGImageRef createRefWithNoCopyPixels(const void* pixels, int width, int height)
    {
        void* buffer = (void*)pixels;
        int bufferLength = width * height * 4;
        CGDataProviderReleaseDataCallback releaseDataCallBack = NULL;

        // 设置Bitmap信息
        CGDataProviderRef provider =
            CGDataProviderCreateWithData(NULL, buffer, bufferLength, releaseDataCallBack);
        CF_SCOPE_RELEASE(provider);

        int bitsPerComponent = 8;
        int bitsPerPixel = 32;
        int bytesPerRow = 4 * (int)width;
        CGColorSpaceRef colorSpaceRef = CGColorSpaceCreateDeviceRGB();
        CF_SCOPE_RELEASE(colorSpaceRef);

        CGBitmapInfo bitmapInfo = (kCGBitmapByteOrder32Big | kCGImageAlphaPremultipliedLast);

        // 创建Bitmap图片
        CGImageRef imageRef = CGImageCreate(width,
                                            height,
                                            bitsPerComponent,
                                            bitsPerPixel,
                                            bytesPerRow,
                                            colorSpaceRef,
                                            bitmapInfo,
                                            provider,
                                            NULL,
                                            false,
                                            kCGRenderingIntentDefault);
        return imageRef;
    }

    QuartzImage::QuartzImage(CGImageRef image)
    {
        _image = NULL;
        if (image)
        {
            _image = CGImageRetain(image);
        }
    }

    QuartzImage::~QuartzImage()
    {
        if (_image)
        {
            CGImageRelease(_image);
        }
    }

    Size QuartzImage::getSize() const
    {
        if (_bitmapData)
        {
            return Size(_bitmapData->getWidth(), _bitmapData->getHeight());
        }
        if (_image == NULL)
        {
            return Size();
        }
        return Size(CGImageGetWidth(_image), CGImageGetHeight(_image));
    }

    QuartzImage::Ptr QuartzImage::create(CGImageRef image)
    {
        return Ptr(new QuartzImage(image), false);
    }

    QuartzImage::Ptr QuartzImage::create()
    {
        return Ptr(new QuartzImage(NULL), false);
    }

    QuartzImage::Ptr QuartzImage::create(const fla::BitmapData::Ptr& bitmapData)
    {
        return Ptr(new QuartzImage(bitmapData), false);
    }

    QuartzImage::QuartzImage(const fla::BitmapData::Ptr& bitmapData)
    {
        _bitmapData = bitmapData;
        _image = nullptr;
    }

    CGImageRef QuartzImage::getImage() const
    {
        return _image;
    }

    void QuartzImage::savePng(const std::string& path)
    {
        if (_bitmapData)
        {
            assert(_bitmapData->isFormat8888());
            auto ref = createRefWithNoCopyPixels(_bitmapData->getPixels(),
                                                 _bitmapData->getWidth(),
                                                 _bitmapData->getHeight());
            CF_SCOPE_RELEASE(ref);
            writePNGToFile(ref, path);
        }
        else
        {
            writePNGToFile(_image, path);
        }
    }
}

#endif
