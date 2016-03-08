//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#include "fla_TextureFrame.h"
#include "fla_Settings.h"
#include "fla_MovieShareData.h"
#include "fla_Settings.h"
#include "clover/ScopeGuard.h"
using namespace cocos2d;

namespace fla
{
#if CC_SPRITEBATCHNODE_RENDER_SUBPIXEL
#define RENDER_IN_SUBPIXEL
#else
#define RENDER_IN_SUBPIXEL(__ARGS__) (ceil(__ARGS__))
#endif

    template <typename T>
    inline T* offset_ptr(T* ptr, size_t stride)
    {
        return reinterpret_cast<T*>(reinterpret_cast<char*>(ptr) + stride);
    }

    static void s_setQuard(gles::Quad* quad, const gles::Rect2& rect, size_t offset)
    {
        auto ptr = reinterpret_cast<gles::CoordPoint*>(quad);
        ptr = offset_ptr(ptr, offset);
        *ptr = rect.topLeft();
        ptr = offset_ptr(ptr, sizeof(gles::Coord));
        *ptr = rect.bottomLeft();
        ptr = offset_ptr(ptr, sizeof(gles::Coord));
        *ptr = rect.topRight();
        ptr = offset_ptr(ptr, sizeof(gles::Coord));
        *ptr = rect.bottomRight();
    }

    static inline void s_setPosition(gles::CoordPoint& pt, real_t x, real_t y)
    {
        pt.x = RENDER_IN_SUBPIXEL(x);
        pt.y = RENDER_IN_SUBPIXEL(y);
    }

    TextureFrame* TextureFrame::create(uint64_t textureId,
                                       const cocos2d_bridge::Rect& rect,
                                       const cocos2d_bridge::Rect& rectInPixels,
                                       bool rotated)
    {
        auto sprite = new TextureFrame(textureId, rect, rectInPixels, rotated);
        sprite->autorelease();
        return sprite;
    }

    TextureFrame::~TextureFrame()
    {
        CC_SAFE_RELEASE(_texture2d);
    }

    TextureFrame::TextureFrame(uint64_t textureId,
                               const cocos2d_bridge::Rect& rect,
                               const cocos2d_bridge::Rect& rectInPixels,
                               bool rotated)
    {
        assert(textureId > 0);
        _textureId = textureId;
        _texture2d = nullptr;
        _rect = rect;
        _rectInPixels = rectInPixels;
        _rotated = rotated;
        _quadIsDirty = true;
    }

    void TextureFrame::updateQuad(bool isFixHscreen)
    {
        if (!_quadIsDirty)
        {
            return;
        }

        auto vertRect = gles::MakeRect2(0, _rect.size.height, _rect.size.width, -_rect.size.height);
        s_setQuard(&_quad, vertRect, offsetof(gles::Coord, position));

        auto rectInPixels = _rectInPixels;
        if (isFixHscreen)
        {
            if (_rotated)
            {
                auto offset = (rectInPixels.size.width - 4) / 2;
                rectInPixels.origin.y += offset;
                rectInPixels.size.width -= 2 * offset;
            }
            else
            {
                auto offset = (rectInPixels.size.width - 4) / 2;
                rectInPixels.origin.x += offset;
                rectInPixels.size.width -= 2 * offset;
            }
        }

        float atlasWidth = (float)_texture2d->getPixelsWide();
        float atlasHeight = (float)_texture2d->getPixelsHigh();

        vertRect = gles::MakeRect2(rectInPixels.origin.x,
                                   rectInPixels.origin.y,
                                   rectInPixels.size.width,
                                   rectInPixels.size.height);
        if (_rotated)
        {
            vertRect.rotate();
            vertRect.normalized(atlasWidth, atlasHeight);
            vertRect.flipX();

            _quad.topLeft.texCoords = vertRect.topRight();
            _quad.bottomLeft.texCoords = vertRect.topLeft();
            _quad.topRight.texCoords = vertRect.bottomRight();
            _quad.bottomRight.texCoords = vertRect.bottomLeft();
        }
        else
        {
            vertRect.normalized(atlasWidth, atlasHeight);
            vertRect.flipY();
            s_setQuard(&_quad, vertRect, offsetof(gles::Coord, texCoords));
        }
    }

    cocos2d_bridge::SpriteFrame* TextureFrame::toSpriteFrame() const
    {
        float retinaScale = fla::settings::getTextureContentScale();
        auto oldContentScale = cocos2d_bridge::Director_getInstance()->getContentScaleFactor();
        cocos2d_bridge::Director_getInstance()->setContentScaleFactor(retinaScale);
        CLOVER_SCOPE_EXIT
        {
            cocos2d_bridge::Director_getInstance()->setContentScaleFactor(oldContentScale);
        };

        return cocos2d_bridge::SpriteFrame::createWithTexture(_texture2d,
                                                              _rectInPixels,
                                                              _rotated,
                                                              cocos2d_bridge::Point(0, 0),
                                                              _rectInPixels.size);
    }

    void transformQuadToBatch(const Matrix& transform,
                              const Point& offset,
                              const cocos2d_bridge::Size& size,
                              gles::Quad* quad)
    {
        assert(quad);

        real_t x1 = 0;
        real_t y1 = 0;

        real_t x2 = x1 + size.width;
        real_t y2 = y1 + size.height;

        real_t x = transform.tx;
        real_t y = transform.ty;

        real_t cr = transform.a;
        real_t sr = transform.b;
        real_t cr2 = transform.d;
        real_t sr2 = transform.c;

        x += km::dotMult(cr, sr2, offset.x, offset.y);
        y += km::dotMult(sr, cr2, offset.x, offset.y);

        real_t ax = x1 * cr + y1 * sr2 + x;
        real_t ay = x1 * sr + y1 * cr2 + y;

        real_t bx = x2 * cr + y1 * sr2 + x;
        real_t by = x2 * sr + y1 * cr2 + y;

        real_t cx = x2 * cr + y2 * sr2 + x;
        real_t cy = x2 * sr + y2 * cr2 + y;

        real_t dx = x1 * cr + y2 * sr2 + x;
        real_t dy = x1 * sr + y2 * cr2 + y;

        s_setPosition(quad->bottomLeft.position, ax, ay);
        s_setPosition(quad->bottomRight.position, bx, by);
        s_setPosition(quad->topLeft.position, dx, dy);
        s_setPosition(quad->topRight.position, cx, cy);
    }
}
