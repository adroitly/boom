//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_TPTEXTUREPACKER_H__
#define __FLA_TPTEXTUREPACKER_H__

#include "fla_TPTextureOuput.h"
#include "rbp/rbp_TexturePacker.h"

namespace fla
{
    namespace tp
    {
        class TexturePacker : public rbp::TexturePacker
        {
        public:
            TexturePacker(CalTextureFun calTextureSize);

            bool packShapes(const fla::Definition::Ptr& root, float padding, float scale);
            bool pack(const std::vector<fla::Definition::Ptr>& definitions, float padding, float scale);

            std::vector<TextureOuput> outputBins(PixelFormat pixelFormat) const;
        };
    }
}

#endif
