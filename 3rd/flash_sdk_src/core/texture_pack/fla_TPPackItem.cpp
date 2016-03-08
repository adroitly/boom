//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_TPPackItem.h"
#include "../base/fla_utils.h"

namespace fla
{
    namespace tp
    {
        PackItem::PackItem(const Definition::Ptr& definition, float padding, float scale)
        {
            _definition = definition;
            _scale = scale;
            _padding = padding;

            auto bounds = adjustRectForRender(definition->getBounds(), scale);

            rbp::Rect rt;
            rt.x = bounds.x;
            rt.y = bounds.y;
            rt.width = static_cast<int>(bounds.width) + padding;
            rt.height = static_cast<int>(bounds.height) + padding;

            setBounds(rt);
        }

        PackItem::Ptr PackItem::create(const Definition::Ptr& definition, float padding, float scale)
        {
            if (!definition)
            {
                return PackItem::Ptr();
            }
            return rbp::makeRef<PackItem>(definition, padding, scale);
        }

        rbp::Rect PackItem::getOutpuPackRect() const
        {
            auto rt = getPackRect();
            rt.width -= _padding;
            rt.height -= _padding;
            return rt;
        }

        std::string PackItem::computeItemCacheKey() const
        {
            return keyOfCache(_definition.get(), _scale);
        }

        int PackItem::getItemId() const
        {
            return _definition->getId();
        }
    }
}
