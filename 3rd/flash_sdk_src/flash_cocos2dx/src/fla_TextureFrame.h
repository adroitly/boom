//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_QUICKSPRITE_H__
#define __FLA_QUICKSPRITE_H__

#include "./cocos2d_bridge.h"
#include "../base/fla_Quad.h"
#include "../../core/base/fla_Base.h"
#include "clover/IntrusiveObject.h"
#include "../../core/base/fla_Ref.h"

namespace fla
{
    class TextureFrame : public cocos2d_bridge::Object
    {
    public:
        typedef cocos2d_bridge::Rect Rect;
        ~TextureFrame();

        static TextureFrame* create(uint64_t textureId,
                                    const cocos2d_bridge::Rect& rect,
                                    const cocos2d_bridge::Rect& rectInPixels,
                                    bool rotated);

        void updateQuad(bool isFixHscreen);

        uint64_t getTextureId() const
        {
            return _textureId;
        }

        cocos2d_bridge::Texture2D* getTexture() const
        {
            return _texture2d;
        }

        void setTexture(cocos2d_bridge::Texture2D* texture2d)
        {
            clover::intrusive_ptr_safe_assign(_texture2d, texture2d);
        }

        const gles::Quad& getQuad() const
        {
            return _quad;
        }

        const cocos2d_bridge::Size& getFrameSize() const
        {
            return _rect.size;
        }

        cocos2d_bridge::SpriteFrame* toSpriteFrame() const;

    private:
        TextureFrame(uint64_t textureId,
                     const cocos2d_bridge::Rect& rect,
                     const cocos2d_bridge::Rect& rectInPixels,
                     bool rotated);

    private:
        gles::Quad _quad;
        cocos2d_bridge::Texture2D* _texture2d;
        uint64_t _textureId;
        Rect _rect;
        Rect _rectInPixels;
        bool _rotated;
        bool _quadIsDirty;
    };

    void transformQuadToBatch(const Matrix& transform,
                              const Point& offset,
                              const cocos2d_bridge::Size& frameSize,
                              gles::Quad* quad);
}

#endif
