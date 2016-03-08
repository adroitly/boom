//=============================================================================
//  FlashFire
//
//  Copyright (C) 2015 PatGame. All rights reserved.
//
//  Created by HJC
//
//=============================================================================

#ifndef __FLA_DEFINESCENE_H__
#define __FLA_DEFINESCENE_H__

#include <string>
#include "fla_DefinitionAnimation.h"
#include "../base/fla_Color4.h"

namespace fla
{
    // 场景
    class DefinitionScene : public DefinitionAnimation
    {
    public:
        typedef boost::intrusive_ptr<DefinitionScene> Ptr;
        DefinitionScene() : DefinitionAnimation(DefinitionType::Scene)
        {
        }

        static Ptr create();

        Rect getBounds() const override;

        // 场景大小
        void setSize(const Size& size)
        {
            _size = size;
        }

        const Size& getSize() const
        {
            return _size;
        }

        // 颜色
        void setColor(const Color4& color)
        {
            _color = color;
        }
        
        const Color4& getColor() const
        {
            return _color;
        }

        void accept(DefinitionVisitor& visitor) const override
        {
            visitor.visit(*this);
        }

        virtual void onFinishParse() override
        {
        }

    private:
        Size _size;
        Color4 _color;
    };
}

#endif
