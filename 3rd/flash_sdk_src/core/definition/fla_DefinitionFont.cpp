//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_DefinitionFont.h"

namespace fla
{
    const FontItem* DefinitionFont::findItem(uint16_t code) const
    {
        return const_cast<DefinitionFont*>(this)->findItem(code);
    }

    FontItem* DefinitionFont::findItem(uint16_t code)
    {
        auto iter = _items.find(code);
        if (iter != _items.end())
        {
            return &iter->second;
        }
        return nullptr;
    }

    void DefinitionFont::addItem(const FontItem& item)
    {
        if (_items.empty())
        {
            _defaultCode = item.code;
        }
        _items[item.code] = item;
    }

    Rect DefinitionFont::getBounds() const
    {
        auto item = defaultItem();
        if (!item)
        {
            return Rect();
        }

        if (hasLayout())
        {
            return item->bounds;
        }

        return item->glyph.computeEdgeBounds();
    }
}
