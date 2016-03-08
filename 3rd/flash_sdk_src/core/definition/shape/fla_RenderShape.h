//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_RENDERSHAPE__
#define __FLA_RENDERSHAPE__

#include <assert.h>
#include "fla_Shape.h"
#include "fla_ShapeGraphicsUtils.h"
#include "../../base/fla_ColorTransform.h"
#include "../fla_FlaDataInfo.h"
#include "../fla_DefinitionImage.h"

namespace fla
{
    bool isSolidFill(const Shape& shape, const Path& path);

    template <typename Graphics>
    static void DrawPath(Graphics& graphics, const Path& path)
    {
        if (path.fillStyle() >= 0 && path.lineStyle() >= 0)
        {
            graphics.drawPath(Graphics::PathEOFillStroke);
        }
        else if (path.fillStyle() >= 0)
        {
            graphics.drawPath(Graphics::PathEOFill);
        }
        else if (path.lineStyle() >= 0)
        {
            graphics.drawPath(Graphics::PathStroke);
        }
        else
        {
            graphics.drawPath(Graphics::PathEOFillStroke);
        }
    }

    // 用颜色进行实心填充
    template <typename Graphics>
    void FillSolidStrokePath(const Shape& shape,
                             const Path& path,
                             Graphics& graphics,
                             const ColorTransform& colorTransform)
    {
        if (path.fillStyle() >= 0)
        {
            auto& style = shape.fillStyles[path.fillStyle()];
            assert(style.isSolidStyle());

            auto color = colorTransform * style.solidColor();
            graphics.setFillColor(color.red, color.green, color.blue, color.alpha);
        }

        if (path.lineStyle() >= 0)
        {
            auto& style = shape.lineStyles[path.lineStyle()];

            auto color = colorTransform * style.color;
            graphics.setLineWidth(std::max<real_t>(style.width, 1.0));
            graphics.setStrokeColor(color.red, color.green, color.blue, color.alpha);
        }

        shape::GenPath(graphics, path, true);
        DrawPath(graphics, path);
    }

    // 渐变填充
    template <typename Graphics>
    void FillGradientPath(const Shape& shape,
                          const Path& path,
                          Graphics& graphics,
                          const ColorTransform& colorTransform)
    {
        assert(path.fillStyle() >= 0);
        auto& style = shape.fillStyles[path.fillStyle()];
        assert(style.isGradientStyle());

        shape::GenPath(graphics, path, true);
        auto& ptr = style.gradient();

        auto recSize = ptr.records().size();
        std::vector<Color4> colors(recSize);
        std::vector<real_t> locations(recSize);

        for (size_t i = 0; i < recSize; i++)
        {
            colors[i] = colorTransform * ptr.records()[i].color;
            locations[i] = ptr.records()[i].location;
        }

        graphics.drawGradient(colors,
                              locations,
                              style.fillType() == FillType::LinearGradient,
                              ptr.radius(),
                              ptr.matrix().val);
    }

    // 填充并描边
    template <typename Graphics>
    static void FillSolidPath(const Shape& shape,
                              const Path& path,
                              Graphics& graphics,
                              const ColorTransform& colorTransform)
    {
        assert(path.fillStyle() >= 0);
        auto& style = shape.fillStyles[path.fillStyle()];
        assert(style.isSolidStyle());

        shape::GenPath(graphics, path, true);
        Color4 color = colorTransform * style.solidColor();
        graphics.setFillColor(color.red, color.green, color.blue, color.alpha);
        graphics.drawPath(Graphics::PathEOFill);
    }

    // 用位图填充
    template <typename Graphics>
    static void FillBitmapPath(const Shape& shape,
                               const Path& path,
                               Graphics& graphics,
                               const FlaDataInfoWithImages::Ptr& fileDataInfo)
    {
        assert(path.fillStyle() >= 0);
        auto& style = shape.fillStyles[path.fillStyle()];
        assert(style.isBitmapStyle());

        if (fileDataInfo)
        {
            auto img = fileDataInfo->findImage(style.bitmapId());
            if (img && img->getImage())
            {
                shape::GenPath(graphics, path, true);
                graphics.drawImage(img->getSize(), *img->getImage(), style.bitmapMatrix());
            }
        }
    }

    // 填充
    template <typename Graphics>
    static void FillPath(const Shape& shape,
                         const Path& path,
                         Graphics& graphics,
                         const ColorTransform& colorTransform,
                         const FlaDataInfoWithImages::Ptr& fileDataInfo)
    {
        if (path.fillStyle() < 0)
        {
            return;
        }

        auto& style = shape.fillStyles[path.fillStyle()];
        if (style.isSolidStyle())
        {
            FillSolidPath(shape, path, graphics, colorTransform);
        }
        else if (style.isGradientStyle())
        {
            FillGradientPath(shape, path, graphics, colorTransform);
        }
        else if (style.isBitmapStyle())
        {
            FillBitmapPath(shape, path, graphics, fileDataInfo);
        }
    }

    // 描边
    template <typename Graphics>
    void StrokePath(const Shape& shape, const Path& path, Graphics& graphics)
    {
        if (path.lineStyle() >= 0)
        {
            auto& style = shape.lineStyles[path.lineStyle()];
            Color4 color = style.color;

            graphics.setLineWidth(std::max<real_t>(style.width, 1.0));
            graphics.setStrokeColor(color.red, color.green, color.blue, color.alpha);

            if (!style.onlyWidthAndColor)
            {
                graphics.setLineCap(shape::_lineCap<Graphics>(style.startCapStyle));
                graphics.setMiterLimit(style.miterLimitFactor);
                graphics.setLineJoin(shape::_lineJoint<Graphics>(style.jointStyle));
            }
            else
            {
                graphics.setLineCap(Graphics::LineCapRound);
                graphics.setLineJoin(Graphics::LineJoinBevel);
            }

            shape::GenPath(graphics, path, false);
            graphics.drawPath(Graphics::PathStroke);
        }

        for (auto& holePath : path.subPaths())
        {
            StrokePath(shape, holePath, graphics);
        }
    }

    // 渲染矢量图
    template <typename Graphics>
    void renderShape(Graphics& graphics,
                     const Shape& shape,
                     const ColorTransform& colorTransform,
                     const FlaDataInfoWithImages::Ptr& fileDataInfo)
    {
        if (shape.hasStyle())
        {
            for (auto& iter : shape.paths)
            {
                graphics.saveGState();
                if (iter.isSameLineStyle() && isSolidFill(shape, iter))
                {
                    FillSolidStrokePath(shape, iter, graphics, colorTransform);
                }
                else
                {
                    FillPath(shape, iter, graphics, colorTransform, fileDataInfo);
                    StrokePath(shape, iter, graphics);
                }
                graphics.restoreGState();
            }
        }
        else
        {
            for (auto& iter : shape.paths)
            {
                shape::GenPath(graphics, iter, true);
                DrawPath(graphics, iter);
            }
        }
    }
}

#endif
