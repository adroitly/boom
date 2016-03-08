//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_DefinitionShape.h"
#include "./bin/fla_BinParseShape.h"

namespace fla
{
    const Shape& DefinitionShape::getShape() const
    {
        if (_shape.isEmpty() && !_rawData.empty())
        {
            auto ptr = _rawData.begin();
            fla::parseSingleShape(_shape, ptr);
            _rawData.clear();
        }
        return _shape;
    }

    void DefinitionShape::swapShape(Shape& shape)
    {
        _shape.swap(shape);
    }

    void DefinitionShape::setBounds(const Rect& bounds)
    {
        _shapeBounds = bounds;
    }
    
    Rect DefinitionShape::getBounds() const
    {
        return _shapeBounds;
    }

    void DefinitionShape::onFinishParse()
    {
        _shape.shrink_to_fit();
    }

    void DefinitionShape::setRawData(const uint8_t* data, size_t size)
    {
        _rawData.reset(data, size);
    }

    boost::intrusive_ptr<DefinitionImage> DefinitionShape::findImage(int Id)
    {
        if (getDataInfo())
        {
            auto info = fla::ptr_case<FlaDataInfoWithImages>(getDataInfo());
            return info->findImage(Id);
        }
        return boost::intrusive_ptr<DefinitionImage>();
    }
}
