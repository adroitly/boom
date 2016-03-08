//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_DEFINETEXT__
#define __FLA_DEFINETEXT__

#include "fla_Definition.h"
#include "fla_DefinitionFont.h"
#include "Shape/fla_RenderShape.h"
#include <vector>

namespace fla
{
    class GlyphEntry
    {
    public:
        GlyphEntry() : code(0), advance(0)
        {
        }
        uint16_t code;
        float advance;
    };

    ///////////////////////////////////////////////////////////////////////////////

    class TextRecord
    {
    public:
        TextRecord() : textHeight(10)
        {
        }

        bool hasFont() const
        {
            return ((styleFlags & 0x08) != 0);
        }
        
        bool hasColor() const
        {
            return ((styleFlags & 0x04) != 0);
        }
        
        bool hasYOffset() const
        {
            return ((styleFlags & 0x02) != 0);
        }
        
        bool hasXOffset() const
        {
            return ((styleFlags & 0x01) != 0);
        }

        uint8_t styleFlags;
        real_t textHeight;
        fla::DefinitionFont::Ptr font;
        Point offset;
        Color4 color;
        std::vector<GlyphEntry> glyphEntries;
    };

    /////////////////////////////////////////////////////////////////////////////////
    class DefinitionText : public DefinitionHelper<DefinitionText>
    {
    public:
        void setTextBounds(const Rect& rt)
        {
            _textBounds = rt;
        }
        
        const Rect& textBounds() const
        {
            return _textBounds;
        }
        
        virtual Rect getBounds() const override
        {
            return _textBounds;
        }

        void setTextMatrix(const Matrix& matrix)
        {
            _textMatrix = matrix;
        }
        
        const Matrix& textMatrix() const
        {
            return _textMatrix;
        }

        std::vector<TextRecord>& records()
        {
            return _records;
        }
        
        const std::vector<TextRecord>& records() const
        {
            return _records;
        }

        template <typename Graphics>
        void render(Graphics& context) const;

        virtual void onFinishParse() override
        {
        }

    private:
        friend class DefinitionHelper<DefinitionText>;
        DefinitionText()
        {
        }

    private:
        Rect _textBounds;
        Matrix _textMatrix;
        std::vector<TextRecord> _records;
    };

    typedef struct
    {
        Point offset;
        real_t scale;
        DefinitionFont::Ptr font;
    } DrawTextInfo;

    template <typename Graphics>
    void drawRecord(Graphics& graphics, const TextRecord& r, DrawTextInfo& drawInfo)
    {
        if (r.hasColor())
        {
            graphics.setFillColor(r.color.red, r.color.green, r.color.blue, r.color.alpha);
        }

        if (r.hasFont())
        {
            real_t oldScale = drawInfo.scale;
            drawInfo.font = r.font;
            drawInfo.scale = 1024 / r.textHeight;
            graphics.scaleCTM(oldScale / drawInfo.scale, oldScale / drawInfo.scale);
        }

        if (r.hasXOffset() || r.hasYOffset())
        {
            auto oldOffset = drawInfo.offset;
            if (r.hasXOffset())
            {
                drawInfo.offset.x = r.offset.x * drawInfo.scale;
            }
            if (r.hasYOffset())
            {
                drawInfo.offset.y = r.offset.y * drawInfo.scale;
            }
            graphics.translateCTM(drawInfo.offset.x - oldOffset.x, drawInfo.offset.y - oldOffset.y);
        }

        if (!drawInfo.font)
        {
            return;
        }

        for (auto& en : r.glyphEntries)
        {
            auto item = drawInfo.font->findItem(en.code);
            if (item)
            {
                renderShape(graphics, item->glyph, ColorTransform::identity(), FlaDataInfoWithImages::Ptr());
                graphics.translateCTM(en.advance * drawInfo.scale, 0);
                drawInfo.offset.x += en.advance * drawInfo.scale;
            }
        }
    }

    template <typename Graphics>
    void DefinitionText::render(Graphics& render) const
    {
        render.saveGState();
        render.concatCTM(_textMatrix);

        DrawTextInfo drawInfo;
        drawInfo.offset.set(0, 0);
        drawInfo.scale = 1.0;

        for (auto& r : _records)
        {
            drawRecord(render, r, drawInfo);
        }

        render.restoreGState();
    }
}

#endif
