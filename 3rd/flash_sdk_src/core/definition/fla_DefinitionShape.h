//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_DEFINESHAPE__
#define __FLA_DEFINESHAPE__

#include <vector>
#include "fla_Definition.h"
#include "./shape/fla_Shape.h"
#include "./shape/fla_RenderShape.h"
#include "./bin/fla_BinParseShape.h"

namespace fla
{
    class ColorTransform;
    class DefinitionShape : public DefinitionHelper<DefinitionShape>
    {
    public:
        void setBounds(const Rect& bounds);
        Rect getBounds() const override;

        template <typename Graphics>
        void render(Graphics& graphics, const ColorTransform& colorTrans) const;

        const Shape& getShape() const;
        void swapShape(Shape& shape);

        void onFinishParse() override;
        void setRawData(const uint8_t* data, size_t size);

        FlaDataInfoWithImages::Ptr getDataInfoWithImages() const
        {
            return fla::ptr_case<FlaDataInfoWithImages>(getDataInfo());
        }

        boost::intrusive_ptr<DefinitionImage> findImage(int Id);

    private:
        friend class DefinitionHelper<DefinitionShape>;
        DefinitionShape()
        {
        }

    private:
        Rect _shapeBounds;
        mutable Shape _shape;
        mutable RawData _rawData;
    };

    template <typename Graphics>
    void DefinitionShape::render(Graphics& graphics, const ColorTransform& colorTrans) const
    {
        auto dataInfo = getDataInfoWithImages();
        if (_shape.isEmpty() && !_rawData.empty())
        {
            Shape tmpShape;
            auto ptr = _rawData.begin();
            fla::parseSingleShape(tmpShape, ptr);
            renderShape(graphics, tmpShape, colorTrans, dataInfo);
        }
        else
        {
            renderShape(graphics, _shape, colorTrans, dataInfo);
        }
    }
}

#endif
