//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_DEFINEIMAGE__
#define __FLA_DEFINEIMAGE__

#include <vector>
#include "../base/fla_ColorTransform.h"
#include "../base/fla_Image.h"
#include "fla_Definition.h"

namespace fla
{
    class DefinitionImage : public DefinitionHelper<DefinitionImage>
    {
    public:
        void setSize(const Size& size)
        {
            _size = size;
        }

        const Size& getSize() const
        {
            return _size;
        }

        Rect getBounds() const override
        {
            assert(_size.width > 0 && _size.height > 0);
            return Rect(0, 0, _size.width, _size.height);
        }

        void setImage(const Image::Ptr& image)
        {
            _image = image;
        }

        const Image::Ptr getImage() const
        {
            return _image;
        }

        bool isSupportScale() const
        {
            return _image ? _image->isSupportScale() : false;
        }

        template <typename Graphics>
        void render(Graphics& graphics, const ColorTransform& colorTrans) const;

        virtual void onFinishParse() override
        {
        }

    private:
        Size _size;
        Image::Ptr _image;
    };
    
    
    template <typename Graphics>
    void DefinitionImage::render(Graphics& graphics, const ColorTransform& colorTrans) const
    {
        FLA_UNUSED(colorTrans);
        if (_image)
        {
            graphics.drawImage(_size, *_image, getBounds());
        }
    }
}

#endif
