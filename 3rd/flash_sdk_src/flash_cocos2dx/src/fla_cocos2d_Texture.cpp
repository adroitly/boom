//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_cocos2d_Texture.h"
#include "cocos2d_bridge.h"
#include "../../core/definition/bin/fla_BinaryReader.h"
#include "../../core/definition/fla_DefinitionUtils.h"
#include "../../core/definition/fla_Definition.h"
#include "../../core/platform/fla_PlatformTraits.h"
#include "../../core/base/fla_utils.h"
#include "libra/libra_math.h"
#include "fla_Settings.h"
using namespace cocos2d;

namespace fla
{
    cocos2d_bridge::Texture2D* definition_transToTexture(Definition* _impl,
                                                         float scale,
                                                         float ratio,
                                                         PixelFormat format)
    {
        auto bitmapData = fla::transToBitmapData(_impl, scale, ratio, (fla::PixelFormat)format);
        return fla::bitmap_transToTexture(bitmapData, (fla::PixelFormat)format);
    }

    BitmapData::Ptr transToBitmapData(const Definition::Ptr& definition, float scale, float ratio, PixelFormat format)
    {
        float retinaScale = fla::settings::getTextureContentScale();
        auto wholeScale = retinaScale * scale;
        auto rt = adjustRectForRender(definition->getBounds(), wholeScale);

        long textureWidth = static_cast<long>(rt.width);
        long textureHeight = static_cast<long>(rt.height);

        if (!cocos2d_bridge::Configuration_getInstance()->supportsNPOT())
        {
            textureWidth = libra_next_pot(textureWidth);
            textureHeight = libra_next_pot(textureHeight);
        }

        PlatformTraits::BitmapGraphics graphics((int)textureWidth, (int)textureHeight, format);
        graphics.flipAndScale(wholeScale);
        graphics.translateCTM(-rt.x, -rt.y);

        if (definition->getType() == DefinitionType::MorphShape)
        {
            auto& shape = static_cast<const DefinitionMorphShape&>(*definition);
            shape.render(graphics, ColorTransform::identity(), ratio);
        }

        else
        {
            Definition_drawInGraphics(*definition, graphics);
        }

        auto bitmapData = graphics.getBitmapData();
        bitmapData->setContentSize(rt.width, rt.height);
        return bitmapData;
    }

    // Texture2D没有setHasPremultipliedAlpha接口，不能修改
    // hasPremultipliedAlpha的值，所以通过继承来绕过这个限制
    class UglyHackedTexture2D : public cocos2d_bridge::Texture2D
    {
    public:
        void setHasPremultipliedAlpha(bool flag)
        {
#if COCOS2D_VERSION >= 0x00030000
            _hasPremultipliedAlpha = flag;
#else
            m_bHasPremultipliedAlpha = flag;
#endif
        }
    };

    static cocos2d_bridge::Texture2D* s_bitmap_transToTexture(const BitmapData& bitmapData)
    {
        auto resultFormat = cocos2d_bridge::kTexture2DPixelFormat_RGBA4444;
        if (bitmapData.isFormat8888())
        {
            resultFormat = cocos2d_bridge::kTexture2DPixelFormat_RGBA8888;
        }

        auto texture = new UglyHackedTexture2D();
        auto contentWidth = bitmapData.getContentWidth();
        auto contentHeight = bitmapData.getContentHeight();

        if (cocos2d_bridge::Texture2D_initWithData(texture,
                                                   bitmapData.getPixels(),
                                                   bitmapData.getPixelLength(),
                                                   resultFormat,
                                                   bitmapData.getWidth(),
                                                   bitmapData.getHeight(),
                                                   cocos2d_bridge::Size(contentWidth, contentHeight)))
        {
            texture->setHasPremultipliedAlpha(true);
            texture->autorelease();
            return texture;
        }
        texture->release();
        return nullptr;
    }

    cocos2d_bridge::Texture2D* bitmap_transToTexture(const BitmapData::Ptr& bitmapData, PixelFormat format)
    {
        if (!bitmapData)
        {
            return nullptr;
        }

        if (bitmapData->getPixelFormat() == format)
        {
            return s_bitmap_transToTexture(*bitmapData);
        }
        auto tmpData = bitmapData->changePixelFormat(format);
        return s_bitmap_transToTexture(*tmpData);
    }

    static BitmapData::Ptr s_image8888To4444(cocos2d_bridge::Image* image)
    {
        assert(cocos2d_bridge::Image_is8888(image));
        auto bitmapData = BitmapData::create(image->getData(),
                                             false,  // don't copy pixels
                                             image->getWidth(),
                                             image->getHeight(),
                                             PixelFormat::RGBA8888);
        return bitmapData->changePixelFormat(PixelFormat::RGBA4444);
    }

    static cocos2d_bridge::Texture2D* texture_image8888To4444(cocos2d_bridge::Image* image)
    {
        auto data = s_image8888To4444(image);
        return s_bitmap_transToTexture(*data);
    }

    static bool s_loadPngImageFromFile(const std::string& fullPath, cocos2d_bridge::Image& image)
    {
        return cocos2d_bridge::loadPngImageFromFile(fullPath, image);
    }

    bool saveBitmapToPngFile(const BitmapData::Ptr& bitmapData, const std::string& filePath)
    {
        if (bitmapData == nullptr)
        {
            return false;
        }
        auto image = fla::PlatformTraits::Image::create(bitmapData);
        image->savePng(filePath);
        return true;
    }

    BitmapData::Ptr loadBitmapFromPngFile(const std::string& fullpath, PixelFormat format)
    {
        cocos2d_bridge::Image image;
        if (!s_loadPngImageFromFile(fullpath, image))
        {
            return nullptr;
        }

        bool imageIs8888 = cocos2d_bridge::Image_is8888(&image);
        if (imageIs8888 && format == PixelFormat::RGBA4444)
        {
            return s_image8888To4444(&image);
        }

        if (imageIs8888 && format == PixelFormat::RGBA8888)
        {
            return BitmapData::create(image.getData(),
                                      true,
                                      image.getWidth(),
                                      image.getHeight(),
                                      PixelFormat::RGBA8888);
        }

        return BitmapData::create(image.getData(), true, image.getWidth(), image.getHeight(), PixelFormat::RGBA4444);
    }

    cocos2d_bridge::Texture2D* texture_loadPngFromFile(const std::string& fullpath, PixelFormat format)
    {
        cocos2d_bridge::Image image;
        if (!s_loadPngImageFromFile(fullpath, image))
        {
            return nullptr;
        }

        if (cocos2d_bridge::Image_is8888(&image) && format == PixelFormat::RGBA4444)
        {
            return texture_image8888To4444(&image);
        }

        cocos2d_bridge::Texture2D* texture2d = new cocos2d_bridge::Texture2D();
        if (texture2d->initWithImage(&image))
        {
            texture2d->autorelease();
            return texture2d;
        }
        texture2d->release();
        return nullptr;
    }
}
