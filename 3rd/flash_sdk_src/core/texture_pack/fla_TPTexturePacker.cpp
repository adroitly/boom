//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_TPTexturePacker.h"
#include "fla_TPPackItem.h"
#include "clover/Container.h"

namespace fla
{
    namespace tp
    {
        template <typename VT>
        bool s_pack(TexturePacker* packer, const VT& v, float padding, float scale)
        {
            auto items = clover::transform(v,
                                           [&](const fla::Definition::Ptr& def)
                                           {
                                               return PackItem::create(def, padding, scale);
                                           });
            return packer->packItems(items);
        }

        TexturePacker::TexturePacker(CalTextureFun calTextureSize) : rbp::TexturePacker(calTextureSize)
        {
        }

        bool TexturePacker::pack(const std::vector<fla::Definition::Ptr>& definitions, float padding, float scale)
        {
            return s_pack(this, definitions, padding, scale);
        }

        bool TexturePacker::packShapes(const fla::Definition::Ptr& root, float padding, float scale)
        {
            // 检查输入参数
            if (!root || scale == 0)
            {
                return false;
            }

            std::set<fla::Definition::Ptr> shapes;
            extractAllShapes(shapes, root);

            return s_pack(this, shapes, padding, scale);
        }

        std::vector<TextureOuput> TexturePacker::outputBins(PixelFormat pixelformat) const
        {
            auto& bins = getBins();
            return clover::transform(bins,
                                     [&](const rbp::TextureBin::Ptr& bin)
                                     {
                                         return textureBinOutput(*bin, pixelformat);
                                     });
        }
    }
}
