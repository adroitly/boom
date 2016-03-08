//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_transToImage.h"
#include "../definition/fla_DefinitionUtils.h"
#include "../base/fla_ColorTransform.h"
#include "../base/fla_utils.h"
#include "../platform/fla_PlatformTraits.h"
#include "fla_RenderOfDefinition.h"

namespace fla
{
    Image::Ptr Definition_transToImage(const Definition& definition, PixelFormat pixelFormat, float scale)
    {
        auto rt = adjustRectForRender(definition.getBounds(), scale);

        PlatformTraits::BitmapGraphics bitmapGraphics(rt.width, rt.height, pixelFormat);
        bitmapGraphics.flipAndScale(scale);

        // 设置缩放比例，和位置调整
        bitmapGraphics.translateCTM(-rt.x, -rt.y);

        RenderOfDefinition<PlatformTraits::Graphics> renderVisitor(bitmapGraphics, ColorTransform::identity());
        definition.accept(renderVisitor);

        return bitmapGraphics.createImage();
    }

    void Definition_render(const Definition& definition, PlatformTraits::Graphics& graphics, const Size& size)
    {
        Rect rt = definition.getBounds();
        auto scale = std::min(size.width / rt.width, size.height / rt.height);

        Point offset;
        offset.x = (size.width - rt.width * scale) * 0.5;
        offset.y = (size.height - rt.height * scale) * 0.5;

        graphics.clipToRect(Rect(offset.x, offset.y, rt.width * scale, rt.height * scale));
        graphics.translateCTM(offset.x, offset.y);
        graphics.scaleCTM(scale, scale);

        // 设置缩放比例，和位置调整
        graphics.translateCTM(-rt.x, -rt.y);

        RenderOfDefinition<PlatformTraits::Graphics> renderVisitor(graphics, ColorTransform::identity());
        definition.accept(renderVisitor);
    }

    Image::Ptr Definition_transToImage(const Definition& definition, PixelFormat pixelFormat, const Size& size)
    {
        PlatformTraits::BitmapGraphics bitmapGraphics(size.width, size.height, pixelFormat);
        bitmapGraphics.flipAndScale(1.0);
        Definition_render(definition, bitmapGraphics, size);
        return bitmapGraphics.createImage();
    }
}
