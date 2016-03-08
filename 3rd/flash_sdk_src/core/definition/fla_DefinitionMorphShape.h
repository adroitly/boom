//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_DEFINEMORPHSHAPE__
#define __FLA_DEFINEMORPHSHAPE__

#include "fla_Definition.h"
#include "../Utility/fla_Holder.h"
#include "./Shape/fla_Shape.h"
#include "../Base/fla_ColorTransform.h"
#include "./Shape/fla_ShapeGraphicsUtils.h"
#include "./Shape/fla_RenderShape.h"
#include "libra/libra_math.h"

namespace fla
{
    class DefinitionMorphShape : public DefinitionHelper<DefinitionMorphShape>
    {
    public:
        typedef Holder<Rect, 2> RectT;

        const RectT& bounds() const;
        void setBounds(const RectT& bounds);

        const MorphShape& getShape() const;
        void swapShape(MorphShape& shape);

        void setRawData(const uint8_t* data, size_t size);

        template <typename Graphics>
        void render(Graphics& graphics, const ColorTransform& colorTrans, float ratio) const;

        virtual void onFinishParse() override;

        FlaDataInfoWithImages::Ptr getDataInfoWithImages() const
        {
            return fla::ptr_case<FlaDataInfoWithImages>(getDataInfo());
        }

        virtual Rect getBounds() const override;

    private:
        friend class DefinitionHelper<DefinitionMorphShape>;
        DefinitionMorphShape()
        {
        }

    private:
        template <typename Graphics>
        void fillPath(const MorphPath& path, Graphics& graphics, const ColorTransform& colorTrans, real_t ratio) const;

        template <typename Graphics>
        void strokePath(const MorphPath& path,
                        Graphics& graphics,
                        const ColorTransform& colorTrans,
                        real_t ratio) const;

    private:
        RectT _bounds;
        mutable MorphShape _shape;
        mutable RawData _rawData;
    };

    template <typename Graphics>
    void DefinitionMorphShape::fillPath(const MorphPath& path,
                                        Graphics& graphics,
                                        const ColorTransform& colorTrans,
                                        real_t ratio) const
    {
        if (!path.hasFillStyle())
        {
            return;
        }

        auto& style = getShape().fillStyles[path.fillStyle()];
        if (style.isSolidStyle())
        {
            shape::GenMorphPath(graphics, path, ratio, true);
            auto color = lerp(style.solidColor().start, style.solidColor().end, ratio);
            color = colorTrans * color;
            graphics.setFillColor(color.red, color.green, color.blue, color.alpha);
            graphics.drawPath(Graphics::PathEOFill);
        }

        else if (style.isGradientStyle())
        {
            shape::GenMorphPath(graphics, path, ratio, true);

            auto& ptr = style.gradient();
            auto matrix = lerp(ptr.matrix().start, ptr.matrix().end, ratio);

            auto recSize = ptr.records().size();
            std::vector<Color4> colors(recSize);
            std::vector<real_t> locations(recSize);

            for (size_t i = 0; i < recSize; i++)
            {
                colors[i] = lerp(ptr.records()[i].color.start, ptr.records()[i].color.end, ratio);
                colors[i] = colors[i];
                locations[i] = libra_lerp(ptr.records()[i].location.start, ptr.records()[i].location.end, ratio);
            }

            graphics.drawGradient(colors,
                                  locations,
                                  style.fillType() == FillType::LinearGradient,
                                  ptr.radius(),
                                  Matrix(matrix));
        }
    }

    template <typename Graphics>
    void DefinitionMorphShape::strokePath(const MorphPath& path,
                                          Graphics& graphics,
                                          const ColorTransform& colorTrans,
                                          real_t ratio) const
    {
        if (path.hasLineStyle())
        {
            auto& style = getShape().lineStyles[path.lineStyle()];
            auto color = lerp(style.color.start, style.color.end, ratio);
            color = colorTrans * color;

            auto lineWidth = libra_lerp(style.width.start, style.width.end, ratio);

            graphics.setLineWidth(std::max<real_t>(lineWidth, 1.0));
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

            shape::GenMorphPath(graphics, path, ratio, false);
            graphics.drawPath(Graphics::PathStroke);
        }

        for (auto& holePath : path.subPaths())
        {
            strokePath(holePath, graphics, colorTrans, ratio);
        }
    }

    template <typename Graphics>
    void DefinitionMorphShape::render(Graphics& graphics, const ColorTransform& colorTrans, float ratio) const
    {
        for (auto& path : getShape().paths)
        {
            fillPath(path, graphics, colorTrans, ratio);
            strokePath(path, graphics, colorTrans, ratio);
        }
    }
}

#endif
