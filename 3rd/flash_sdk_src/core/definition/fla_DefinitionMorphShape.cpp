//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_DefinitionMorphShape.h"
#include "./bin/fla_BinParseShape.h"

namespace fla
{
    const DefinitionMorphShape::RectT& DefinitionMorphShape::bounds() const
    {
        return _bounds;
    }

    void DefinitionMorphShape::setBounds(const RectT& bounds)
    {
        _bounds = bounds;
    }

    const MorphShape& DefinitionMorphShape::getShape() const
    {
        if (_shape.isEmpty() && !_rawData.empty())
        {
            auto ptr = _rawData.begin();
            fla::parseSingleShape(_shape, ptr);
            _rawData.clear();
        }
        return _shape;
    }

    void DefinitionMorphShape::setRawData(const uint8_t* data, size_t size)
    {
        _rawData.reset(data, size);
    }

    void DefinitionMorphShape::onFinishParse()
    {
    }

    void DefinitionMorphShape::swapShape(MorphShape& shape)
    {
        _shape.swap(shape);
    }

    Rect DefinitionMorphShape::getBounds() const
    {
        Rect rt = _bounds.start;
        rt.unionRect(_bounds.end);
        return rt;
    }
}
