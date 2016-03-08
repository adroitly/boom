//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_RENDERDEFINE_H__
#define __FLA_RENDERDEFINE_H__

#include "../definition/fla_DefinitionShape.h"
#include "../definition/fla_DefinitionRole.h"
#include "../definition/fla_DefinitionScene.h"
#include "../definition/fla_DefinitionAnimation.h"
#include "../definition/fla_DefinitionImage.h"
#include "../definition/fla_DefinitionFont.h"
#include "../definition/fla_DefinitionText.h"
#include "../definition/fla_DefinitionMorphShape.h"
#include "../definition/fla_DefinitionPackage.h"
#include "clover/ScopeGuard.h"

namespace fla
{
    // 渲染元件
    template <typename Graphics>
    class RenderOfDefinition : public DefinitionVisitor
    {
    public:
        RenderOfDefinition(Graphics& graphics, const ColorTransform& colorTrans);

        virtual void visit(const DefinitionShape& shape) override;       // 形状
        virtual void visit(const DefinitionRole& role) override;         // 角色
        virtual void visit(const DefinitionScene& scene) override;       // 场景
        virtual void visit(const DefinitionAnimation& sprite) override;  // 动画
        virtual void visit(const DefinitionFont& font) override;         // 字体
        virtual void visit(const DefinitionText&) override;              // 文字
        virtual void visit(const DefinitionMorphShape&) override;        // 形变
        virtual void visit(const DefinitionPlaceholder&) override;
        virtual void visit(const DefinitionImage&) override;
        virtual void visit(const DefinitionPackage&) override;

    protected:
        Graphics& _graphics;
        ColorTransform _colorTrans;
    };

    template <typename Graphics>
    RenderOfDefinition<Graphics>::RenderOfDefinition(Graphics& graphics, const ColorTransform& colorTrans)
        : _graphics(graphics), _colorTrans(colorTrans)
    {
    }

    template <typename Graphics>
    void RenderOfDefinition<Graphics>::visit(const DefinitionPlaceholder&)
    {
    }

    template <typename Graphics>
    void RenderOfDefinition<Graphics>::visit(const DefinitionText& text)
    {
        text.render(_graphics);
    }

    template <typename Graphics>
    void RenderOfDefinition<Graphics>::visit(const DefinitionShape& shape)
    {
        shape.render(_graphics, _colorTrans);
    }

    template <typename Graphics>
    void RenderOfDefinition<Graphics>::visit(const DefinitionImage& image)
    {
        image.render(_graphics, _colorTrans);
    }

    template <typename Graphics>
    void RenderOfDefinition<Graphics>::visit(const DefinitionMorphShape& shape)
    {
        shape.render(_graphics, _colorTrans, 0);
    }

    template <typename Graphics>
    void RenderOfDefinition<Graphics>::visit(const DefinitionFont& font)
    {
        auto item = font.defaultItem();
        if (item)
        {
            auto& shape = item->glyph;
            _graphics.setFillColor(0.0, 0, 0, 1);
            renderShape(_graphics, shape, ColorTransform::identity(), FlaDataInfoWithImages::Ptr());
        }
    }

    template <typename Graphics>
    void RenderOfDefinition<Graphics>::visit(const DefinitionRole& role)
    {
        role.defaultState()->accept(*this);
    }

    template <typename Graphics>
    void RenderOfDefinition<Graphics>::visit(const DefinitionScene& scene)
    {
        visit(static_cast<const DefinitionAnimation&>(scene));
    }

    template <typename Graphics>
    void RenderOfDefinition<Graphics>::visit(const DefinitionPackage& package)
    {
        visit(static_cast<const DefinitionAnimation&>(package));
    }

    template <typename Graphics>
    void RenderOfDefinition<Graphics>::visit(const DefinitionAnimation& sprite)
    {
        AnimationFrame frame = sprite.gotoFrame(0);
        for (auto& obj : frame)
        {
            _graphics.saveGState();
            auto saveColor = _colorTrans;
            CLOVER_SCOPE_EXIT
            {
                _colorTrans = saveColor;
                _graphics.restoreGState();
            };

            // 处理位置变换
            if (obj.hasTrans())
            {
                _graphics.concatCTM(obj.trans());
            }

            // 处理颜色变换
            if (obj.hasColorTrans())
            {
                _colorTrans = _colorTrans * obj.colorTrans();
            }

            // 由ID找到对应的元件，再进行渲染
            if (obj.hasCharacterID())
            {
                auto define = sprite.findDefinition(obj.characterID());
                if (define)
                {
                    define->accept(*this);
                }
            }
        }
    }
}

#endif
