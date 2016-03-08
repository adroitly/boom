//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_NULLIMAGE__
#define __FLA_NULLIMAGE__

#include "core/Base/fla_Image.h"
#include "core/Base/fla_BitmapData.h"

namespace fla
{
    class NullImage : public Image
    {
    public:
        static Ptr create(const fla::BitmapData::Ptr& bitmapData)
        {
            return Ptr();
        }

		static Ptr create()
		{
			return Ptr();
		}

        virtual Size getSize() const override
        {
            return Size(0, 0);
        }

        virtual void savePng(const std::string& path) override
        {
        }
    };
}

#endif
